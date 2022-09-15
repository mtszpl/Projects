using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MouseInput : IInputReceiver
{
    [SerializeField] Camera m_playerCamera;
    [SerializeField] LayerMask m_clickable;

    ClickableEntity m_selected;

    override public void Init()
    {
        base.Init();
        InputController.PlugToFire(OnFire);
        InputController.PlugToAltFire(OnAltFire);
    }

    void OnFire(int input)
    {
        if (EventSystem.current.IsPointerOverGameObject())
            return;
        InputController.CloseInterfaces();
        Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, m_clickable))
        {
            ClickableEntity entity = hit.transform.GetComponent<ClickableEntity>();
            if (entity != null)
            {
                entity.m_isSelected = true;
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
        if(m_selected != null)
        {
            Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, Mathf.Infinity, LayerMask.GetMask("Terrain")))
                m_selected.OnAltFire(hit.point);
        }
    }
}
