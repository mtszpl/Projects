using UnityEngine.Audio;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public AudioClip[] m_sounds;
    AudioSource m_source;

    private void Awake()
    {
        m_source = gameObject.GetComponent<AudioSource>();
        m_source.loop = false;
    }

    public void PlaySoundByIndex(int index)
    {
        if (m_source.isPlaying)
            m_source.Stop();
        m_source.clip = m_sounds[index];
        m_source.Play();
    }

}
