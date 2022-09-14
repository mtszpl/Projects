using UnityEngine;

public class playerScriptManager : MonoBehaviour
{
    public playerScript m_GamingScript;
    public keepPlayerUp m_IdleScript;

    public void gameStart()
    {
        m_GamingScript.enabled = true;
        m_IdleScript.enabled = false;
    }

    public void gameEnd()
    {
        m_GamingScript.enabled = false;
    }
}
