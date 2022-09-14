using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IInputReceiver : MonoBehaviour
{
    //[SerializeField] protected InputController m_controller;

    private void Start()
    {
        Init();
    }

    public virtual void Init()
    {
        //if (m_controller == null)
        //    m_controller = transform.parent.GetComponentInChildren<InputController>();
        PlugToController();
    }
    private void PlugToController()
    {
        InputController.PlugToMovement(OnMoveInput);
        InputController.PlugToRotation(OnRotationInput);
        InputController.PlugToPan(OnPan);
        InputController.PlugToScroll(OnScroll);
        InputController.PlugToFasterMove(OnMoveModified);
    }

    private void OnDestroy()
    {
        InputController.UnplugFromMovement(OnMoveInput);
        InputController.UnplugFromRotation(OnRotationInput);
        InputController.UnplugFromPan(OnPan);
        InputController.UnplugFromScroll(OnScroll);
        InputController.UnplugFromFasterMove(OnMoveModified);
    }

    protected virtual void OnMoveInput(Vector2 input)
    {
    }

    protected virtual void OnLookInput(Vector2 input)
    {
    }

    protected virtual void OnRotationInput(Vector2 input)
    {
    }

    protected virtual void OnPan(Vector2 input)
    {
    }

    protected virtual void OnScroll(Vector2 input)
    {
    }

    protected virtual void OnMoveModified(int modifier)
    {
    }
}
