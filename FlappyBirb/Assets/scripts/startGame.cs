using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class startGame : MonoBehaviour
{
    public void playGame()
    {
        Debug.Log("start");
        gameObject.SetActive(false);
    }

    public void quitGame()
    {
        Application.Quit();
        Debug.Log("quit");
    }
}
