using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MouseInput : IInputReceiver
{
    [SerializeField] Camera m_playerCamera;
    [SerializeField] LayerMask m_clickable;


    override public void Init()
    {
        base.Init();
        InputController.PlugToFire(OnClick);
    }

    void OnClick(int input)
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
                entity.OnClick();
        }
    }
}
