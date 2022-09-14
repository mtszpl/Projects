using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class obstacleScript : MonoBehaviour
{
    public float m_Speed = 5f;

    public void gameStart()
    {
        enabled = true;
    }
    public void gameEnd()
    {
        enabled = false;
    }
    void Update()
    {
        Vector3 pos = transform.position;
        pos.x += m_Speed * Time.deltaTime;

        transform.position = pos;

        if (transform.position.x < -10f)
            Destroy(gameObject);
    }

    private void OnCollisionEnter(Collision collision)
    {
        Debug.Log("collision");
    }
}
