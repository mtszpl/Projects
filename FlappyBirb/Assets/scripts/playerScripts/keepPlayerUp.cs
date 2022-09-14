using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class keepPlayerUp : MonoBehaviour
{
    [SerializeField] private Rigidbody2D m_Player;
    [SerializeField] private float m_DesiredYCord = 0f;
    [SerializeField] private float m_JumpForce = 1f;

    void Update()
    {
        if(transform.position.y < m_DesiredYCord)
        {
            m_Player.AddForce(transform.up * m_JumpForce * Time.deltaTime, ForceMode2D.Impulse);
        }
    }
}
