using UnityEngine;
using UnityEngine.UI;

public class playerScript : MonoBehaviour
{
    [SerializeField] private Rigidbody2D m_Player;

    public Text m_ScoreDisplay;

    private float m_Score = 0f;

    public float m_Thrust = 20f;

    void Update()
    {
        if(Input.GetButtonDown("Fire1"))
        {
            m_Player.AddForce(transform.up * m_Thrust, ForceMode2D.Impulse);
        }

        m_Score += 0.5f * Time.deltaTime;
        m_ScoreDisplay.text = m_Score.ToString("F2");
    }
}
