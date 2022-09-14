using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class CameraControlls : IInputReceiver
{
    Camera m_camera;

    [Header("User settings")]
    public float m_moveSensitivity;
    public float m_horizontalRotationSensitivity;
    public float m_verticalRotationSensitivity;
    public float m_panSensivity;
    public float m_zoomSensitivity;

    [Header("Hard Settings")]
    [SerializeField] Transform m_pivot;
    [SerializeField] Vector3 m_cameraOffset;
    [SerializeField] float m_moveModifier = 1;
    [SerializeField] float m_minPitch;
    [SerializeField] float m_maxPitch;
    [SerializeField] float m_maxZoom;
    [SerializeField] float m_minZoom;

    Vector2 m_rotation;
    Quaternion m_cameraRotation;
    Vector3 m_fullRotation;
    Vector2 m_movement;
    float m_distance;

    private void Awake()
    {
        m_camera = gameObject.GetComponentInChildren<Camera>();
        m_camera.transform.position = m_pivot.position + m_cameraOffset;
        m_fullRotation = m_pivot.rotation.eulerAngles;
        m_distance = Vector3.Distance(m_camera.transform.position, transform.position);
    }

    public override void Init()
    {
        base.Init();
    }

    private void Update()
    {
        Move();
        Rotate();
    }

    private void Move()
    {
        transform.Translate(m_movement.x * Time.deltaTime * m_moveModifier * m_distance,
            0,
            m_movement.y * Time.deltaTime * m_moveModifier * m_distance);
    }

    private void Rotate()
    {
        m_rotation *= Time.deltaTime;
        m_fullRotation.x += m_rotation.x;
        m_fullRotation.y -= m_rotation.y;
        m_fullRotation.y = Mathf.Clamp(m_fullRotation.y, m_minPitch, m_maxPitch);

        transform.Rotate(0, m_rotation.x, 0);
        m_pivot.rotation = Quaternion.Euler(m_fullRotation.y, m_fullRotation.x, 0);

        m_camera.transform.LookAt(transform);
    }

    protected override void OnMoveInput(Vector2 input)
    {
        m_movement = input * m_moveSensitivity;
    }

    protected override void OnRotationInput(Vector2 input)
    {
        m_rotation.x = input.x * m_horizontalRotationSensitivity;
        m_rotation.y = input.y * m_verticalRotationSensitivity;
    }

    protected override void OnPan(Vector2 input)
    {
        m_movement = input * m_panSensivity;
    }

    protected override void OnScroll(Vector2 input)
    {
        input *= Time.deltaTime * m_zoomSensitivity;
        m_distance = Vector3.Distance(m_camera.transform.position, transform.position);
        if ((m_distance < m_maxZoom && input.y < 0) || (m_distance > m_minZoom) && input.y > 0)
                m_camera.transform.Translate(0, 0, input.y, Space.Self);
        if(m_camera.transform.position.y < 0)
            m_camera.transform.Translate(0, 0, -input.y, Space.Self);
    }

    protected override void OnMoveModified(int modifier)
    {
        m_moveModifier = modifier;
    }

    
}
