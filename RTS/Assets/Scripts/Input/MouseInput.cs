using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MouseInput : IInputReceiver
{
    [SerializeField] Camera m_playerCamera;
    [SerializeField] LayerMask m_clickable;

    SelectableEntity m_selected;
    List<SelectableEntity> m_selection = new List<SelectableEntity>();

    Vector2 m_startMousePosition;
    Vector2 m_endMOusePosition;
    bool m_isSelecting = false;

    override public void Init()
    {
        base.Init();
        InputController.PlugToFire(OnFire);
        InputController.PlugToFireCancel(SelectGorup);
        InputController.PlugToAltFire(OnAltFire);

        m_startMousePosition = Vector2.zero;
    }

    void OnFire(int input)
    {        
        if (EventSystem.current.IsPointerOverGameObject())
            return;
        DeselectGroup();
        InputController.CloseInterfaces();
        m_isSelecting = true;
        StartCoroutine(HandleSelection());
        Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, m_clickable))
        {
            SelectableEntity entity = hit.transform.GetComponent<SelectableEntity>();
            if (entity != null)
            {
                if (m_selected != null && m_selected != entity)
                    m_selected.OnUnClick();
                entity.OnClick(out m_selected);
            }
        }
        else if(m_selected != null)
        {
            m_selected.OnUnClick();
            m_selected = null;
        }
    }

    void OnAltFire(int input)
    {
        if(m_selection.Count > 0)
        {
            Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, Mathf.Infinity, LayerMask.GetMask("Terrain")))
            {
                foreach(SelectableEntity entity in m_selection)
                    entity.OnAltFire(hit.point);
            }
        }
    }

    IEnumerator HandleSelection()
    {
        m_startMousePosition = Input.mousePosition;
        while (m_isSelecting)
        {
            m_endMOusePosition = Input.mousePosition;
            yield return null;
        }
        //Debug.Log("selection ended");
    }

    void SelectGorup()
    {
        m_isSelecting = false;
        Vector3 box = new Vector3
            (Mathf.Abs(m_startMousePosition.x - m_endMOusePosition.x),
            Mathf.Abs(m_startMousePosition.y - m_endMOusePosition.y), 0);
        Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit[] hits;
        Vector3 cameraPoint = m_playerCamera.ScreenToWorldPoint(box/2);
        hits = Physics.BoxCastAll(box/2, box / 2, ray.GetPoint(100), Quaternion.identity, Mathf.Infinity, m_clickable);
        //Debug.draw
        foreach (RaycastHit hit in hits)
        {
            SelectableEntity entity = hit.collider.GetComponent<SelectableEntity>();
            if (entity != null)
            {
                m_selection.Add(entity);
                SelectableEntity otherEntity = m_selection[m_selection.Count - 1];
                entity.OnClick(out otherEntity);
            }
        }
    }

    void DeselectGroup()
    {
        foreach (SelectableEntity entity in m_selection)
            entity.OnUnClick();
        m_selection.Clear();
    }
}
