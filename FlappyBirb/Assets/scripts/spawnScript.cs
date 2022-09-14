using UnityEngine;

public class spawnScript : MonoBehaviour
{
    [SerializeField] private Transform m_Obstacle;

    [SerializeField] private Transform m_FirstSpawner;
    [SerializeField] private Transform m_SecondSpawner;

    [SerializeField] private float m_Break;

    private float m_Time;
    private Vector3 m_DisplacementVector;

    public void gameStart()
    {
        enabled = true;
    }

    public void gameEnd()
    {
        enabled = false;
    }
    void Start()
    {
        m_Time = m_Break;
        spawn();
    }

    // Update is called once per frame
    void Update()
    {
        m_Time -= Time.deltaTime;

        if (m_Time < 0f)
            spawn();
    }

    void spawn()
    {
        float displacement = Random.Range(-3.8f, 3.8f);
        m_DisplacementVector = m_FirstSpawner.position;
        m_DisplacementVector.y += displacement;

        Instantiate(m_Obstacle, m_DisplacementVector, m_FirstSpawner.rotation);

        m_DisplacementVector = m_SecondSpawner.position;
        m_DisplacementVector.y += displacement;
        Instantiate(m_Obstacle, m_DisplacementVector, m_SecondSpawner.rotation);

        m_Time = m_Break;
    }
}
