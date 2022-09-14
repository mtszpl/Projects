using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class gameManager : MonoBehaviour
{
    bool m_GameIsOver = false;
    [SerializeField] Text m_Punkty;
    [SerializeField] Text m_IloscPunktyy;
    [SerializeField] Text m_GameOverScreen;


    public void playGame()
    {
        m_Punkty.gameObject.SetActive(true);
        m_IloscPunktyy.gameObject.SetActive(true);
        m_IloscPunktyy.text = "0";
    }
    public void gameOver()
    {
        if (!m_GameIsOver)
        {
            m_GameIsOver = true;

            GameObject[] obstacleArray = GameObject.FindGameObjectsWithTag("Obstacle");

            foreach (GameObject obstacle in obstacleArray)
                obstacle.GetComponent<obstacleScript>().enabled = false;

            GameObject.Find("actualSpawner").GetComponent<spawnScript>().enabled = false;

            m_GameOverScreen.gameObject.SetActive(true);
            Debug.Log("U lost noob 2.0 na koniec");
        }
    }

    public void restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
