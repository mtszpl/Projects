using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class TimeManager : MonoBehaviour
{
    GameplayControlls m_timeInput;
    int m_currentTimeScale = 1;

    Vector2Int m_extremalScales = new Vector2Int(-10, 10);

    private void Awake()
    {
        m_timeInput = new GameplayControlls();
        m_timeInput.Player.SpeedUpTime.started += IncreaseSpeed;
        m_timeInput.Player.SlowDownTime.started += DecreaseSpeed;
        m_timeInput.Player.ResetTime.started += ResetSpeed;
    }

    public void IncreaseSpeed(InputAction.CallbackContext context)
    {
        Debug.Log("Fasteeer");
        m_currentTimeScale++;
        if (m_currentTimeScale == 0)
            m_currentTimeScale = 1;
        m_currentTimeScale = Mathf.Clamp(m_currentTimeScale, m_extremalScales.x, m_extremalScales.y);
        Time.timeScale = m_currentTimeScale;
    }

    public void DecreaseSpeed(InputAction.CallbackContext context)
    {
        m_currentTimeScale--;
        if (m_currentTimeScale == 0)
            m_currentTimeScale = -1;
        m_currentTimeScale = Mathf.Clamp(m_currentTimeScale, m_extremalScales.x, m_extremalScales.y);
        Time.timeScale = 1/m_currentTimeScale;
        Debug.Log(Time.timeScale);
    }

    public void ResetSpeed(InputAction.CallbackContext context)
    {
        m_currentTimeScale = 1;
        Time.timeScale = m_currentTimeScale;
        Debug.Log(Time.timeScale);
    }

}
