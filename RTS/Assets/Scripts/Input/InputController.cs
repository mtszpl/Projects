using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.InputSystem;



public class InputController : MonoBehaviour
{
    static InputController m_instance;
    GameplayControlls m_controls;

    UnityEvent<Vector2> m_onMoveInput;
    UnityEvent<Vector2> m_onLookInput;
    UnityEvent<Vector2> m_onRotationInput;
    UnityEvent<Vector2> m_onPanInput;
    UnityEvent<Vector2> m_onScrollInput;
    UnityEvent<int> m_onFasterMove;
    UnityEvent<int> m_onFireInput;
    UnityEvent<int> m_onAltFireInput;
    UnityEvent m_onFireCancel;
    UnityEvent m_closeAllUIs;

    private void Awake()
    {
        m_instance = this;
        m_controls = new GameplayControlls();
        CreateEvents();
    }

    private void CreateEvents()
    {
        if (m_onMoveInput == null)
            m_onMoveInput = new UnityEvent<Vector2>();
        if (m_onLookInput == null)
            m_onLookInput = new UnityEvent<Vector2>();
        if (m_onRotationInput == null)
            m_onRotationInput = new UnityEvent<Vector2>();
        if (m_onPanInput == null)
            m_onPanInput = new UnityEvent<Vector2>();
        if (m_onScrollInput == null)
            m_onScrollInput = new UnityEvent<Vector2>();
        if (m_onFasterMove == null)
            m_onFasterMove = new UnityEvent<int>();
        if (m_onFireInput == null)
            m_onFireInput = new UnityEvent<int>();
        if (m_onAltFireInput == null)
            m_onAltFireInput = new UnityEvent<int>();
        if (m_onFireCancel == null)
            m_onFireCancel = new UnityEvent();
        if (m_closeAllUIs == null)
            m_closeAllUIs = new UnityEvent();
    }

    private void OnEnable()
    {
        m_controls.Player.Enable();

        m_controls.Player.Move.performed += OnMoved;
        m_controls.Player.Move.canceled += OnMoved;

        m_controls.Player.Look.performed += OnLook;
        m_controls.Player.Look.canceled += OnLook;

        m_controls.Player.Look.performed += OnRotated;
        m_controls.Player.Look.canceled += OnRotated;

        m_controls.Player.Pan.performed += OnPanned;
        m_controls.Player.Pan.canceled += OnPanned;

        m_controls.Player.Scroll.performed += OnScrolled;
        m_controls.Player.Scroll.canceled += OnScrolled;

        m_controls.Player.FasterMove.performed += OnFasterMove;
        m_controls.Player.FasterMove.canceled += OnFasterMove;

        m_controls.Player.Fire.performed += OnFire;
        m_controls.Player.Fire.canceled += OnFireCancel;
        m_controls.Player.AltFire.performed += OnAltFire;
    }


    void OnLook(InputAction.CallbackContext context)
    {
        Vector2 input = context.ReadValue<Vector2>();
        m_onLookInput.Invoke(input);
    }

    public static void PlugToLook(UnityAction<Vector2> callback)
    {
        m_instance.m_onLookInput.AddListener(callback);
    }

    public static void UnplugFromLook(UnityAction<Vector2> callback)
    {
        m_instance.m_onLookInput.RemoveListener(callback);
    }

    void OnMoved(InputAction.CallbackContext context)
    {
        Vector2 input = context.ReadValue<Vector2>();
        m_onMoveInput.Invoke(input);
    }

    public static void PlugToMovement(UnityAction<Vector2> callback)
    {
        m_instance.m_onMoveInput.AddListener(callback);
    }

    public static void UnplugFromMovement(UnityAction<Vector2> callback)
    {
        m_instance.m_onMoveInput.RemoveListener(callback);
    }

    void OnRotated(InputAction.CallbackContext context)
    {
        Vector2 input = context.ReadValue<Vector2>();
        m_onRotationInput.Invoke(input);
    }

    public static void PlugToRotation(UnityAction<Vector2> callback)
    {
        m_instance.m_onRotationInput.AddListener(callback);
    }

    public static void UnplugFromRotation(UnityAction<Vector2> callback)
    {
        m_instance.m_onRotationInput.RemoveListener(callback);
    }

    void OnPanned(InputAction.CallbackContext context)
    {
        Vector2 input = context.ReadValue<Vector2>();
        m_onPanInput.Invoke(input);
    }

    public static void PlugToPan(UnityAction<Vector2> callback)
    {
        m_instance.m_onPanInput.AddListener(callback);
    }

    public static void UnplugFromPan(UnityAction<Vector2> callback)
    {
        m_instance.m_onPanInput.RemoveListener(callback);
    }

    void OnScrolled(InputAction.CallbackContext context)
    {
        Vector2 input = context.ReadValue<Vector2>();
        m_onScrollInput.Invoke(input);
    }

    public static void PlugToScroll(UnityAction<Vector2> callback)
    {
        m_instance.m_onScrollInput.AddListener(callback);
    }

    public static void UnplugFromScroll(UnityAction<Vector2> callback)
    {
        m_instance.m_onScrollInput.RemoveListener(callback);
    }

    void OnFasterMove(InputAction.CallbackContext context)
    {
        int input = (int)context.ReadValue<float>();
        m_onFasterMove.Invoke(input + 1);
    }

    public static void PlugToFasterMove(UnityAction<int> callback)
    {
        m_instance.m_onFasterMove.AddListener(callback);
    }

    public static void UnplugFromFasterMove(UnityAction<int> callback)
    {
        m_instance.m_onFasterMove.RemoveListener(callback);
    }

    void OnFire(InputAction.CallbackContext context)
    {
        int input = (int)context.ReadValue<float>();
        m_onFireInput.Invoke(input);
    }
    public static void PlugToFire(UnityAction<int> callback)
    {
        m_instance.m_onFireInput.AddListener(callback);
    }

    public static void UnplugFromFire(UnityAction<int> callback)
    {
        m_instance.m_onFireInput.RemoveListener(callback);
    }

    void OnFireCancel(InputAction.CallbackContext context)
    {
        int input = (int)context.ReadValue<float>();
        m_onFireCancel.Invoke();
    }

    public static void PlugToFireCancel(UnityAction callback)
    {
        m_instance.m_onFireCancel.AddListener(callback);
    }

    public static void UnplugFromFireCancel(UnityAction callback)
    {
        m_instance.m_onFireCancel.RemoveListener(callback);
    }


    void OnAltFire(InputAction.CallbackContext context)
    {
        int input = (int)context.ReadValue<float>();
        m_onAltFireInput.Invoke(input);
    }

    public static void PlugToAltFire(UnityAction<int> callback)
    {
        m_instance.m_onAltFireInput.AddListener(callback);
    }

    public static void UnplugFromAltFire(UnityAction<int> callback)
    {
        m_instance.m_onAltFireInput.RemoveListener(callback);
    }

    public static void CloseInterfaces()
    {
        if(m_instance.m_closeAllUIs != null)
            m_instance.m_closeAllUIs.Invoke();
    }

    public static void PlugToClose(UnityAction callback)
    {
        m_instance.m_closeAllUIs.AddListener(callback);
    }

    public static void UnplugFromClose(UnityAction callback)
    {
        m_instance.m_closeAllUIs.RemoveListener(callback);
    }
}
