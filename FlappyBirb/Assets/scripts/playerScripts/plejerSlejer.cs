using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class plejerSlejer : MonoBehaviour
{
    public playerScript player;
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.tag == "Obstacle")
        {
            player.enabled = false;
            FindObjectOfType<gameManager>().gameOver();
        }
    }
}
