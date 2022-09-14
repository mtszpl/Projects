using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using DG.Tweening;

public class TimeManager : MonoBehaviour
{
    [SerializeField] TMP_InputField m_rounds;
    [SerializeField] TMP_InputField m_work;
    [SerializeField] TMP_InputField m_rest;

    [SerializeField] TMP_Text m_roundDisplay;
    [SerializeField] TMP_Text m_remainingDisplay;
    [SerializeField] TMP_Text m_whatPhase;
    [SerializeField] TMP_Text m_totalTime;
    [SerializeField] RectTransform m_prepareImg;

    [SerializeField] AudioManager m_audioManager;

    int m_allRounds, m_roundsDone;
    int m_workTime;
    int m_restTime;

    int m_currentCounting;

    bool m_isResting;

    int m_prepareTime = 3;

    private void Awake()
    {
        Screen.sleepTimeout = SleepTimeout.NeverSleep;
    }

    public void UpdateTotalTime()
    {
        GetSettings();
        //m_totalTime.text = (m_workTime * m_allRounds + m_restTime * (m_allRounds - 2).ToString();
    }

    public void StartCountdown()
    {
        DOTween.KillAll();
        StopAllCoroutines();
        Init();
        StartCoroutine(Prepare());
    }

    void Init()
    {
        GetSettings();
        m_roundsDone = 0;
        m_roundDisplay.text = (m_roundsDone + 1).ToString();
        m_remainingDisplay.text = m_workTime.ToString();
        m_currentCounting = m_workTime;
        m_isResting = false;
        m_whatPhase.text = "";
    }

    void GetSettings()
    {
        m_workTime = int.Parse(m_work.text);
        m_restTime = int.Parse(m_rest.text);
        m_allRounds = int.Parse(m_rounds.text);
    }

    IEnumerator Prepare()
    {
        m_prepareImg.DOScale(Vector3.one, m_prepareTime/3).SetEase(Ease.Linear);
        yield return new WaitForSecondsRealtime(m_prepareTime);
        m_prepareImg.DOScale(Vector3.zero, m_prepareTime / 3).SetEase(Ease.Linear)
            .OnComplete(() => { m_audioManager.PlaySoundByIndex(0); });
        StartCoroutine(TimerProc());
        yield return null;
    }

    IEnumerator TimerProc()
    {
        m_whatPhase.text = "work";
        m_remainingDisplay.transform.DOScale(new Vector3(0.7f, 0.7f, 0.5f), 0.5f)
            .SetEase(Ease.InOutSine)
            .SetLoops(-1, LoopType.Yoyo);
        while (m_allRounds != m_roundsDone)
        {
            while (m_currentCounting > 0)
            {
                yield return new WaitForSecondsRealtime(1);
                m_currentCounting--;
                m_remainingDisplay.text = m_currentCounting.ToString();
            }
            FlipCounting();
        }
        m_remainingDisplay.transform.DOKill();
        m_remainingDisplay.transform.localScale = Vector3.one;
        m_whatPhase.text = "";
        yield return null;
    }

    void FlipCounting()
    {
        if (m_isResting)
        {
            m_currentCounting = m_workTime;
            m_whatPhase.text = "work";
            m_remainingDisplay.text = m_currentCounting.ToString();
            m_roundDisplay.transform.DOScale(new Vector3(0.7f, 0.7f, 0.5f), 0.25f)
                .SetEase(Ease.InOutSine)
                .SetAutoKill(true)
                .OnComplete(() => {
                    m_roundDisplay.transform.DOScale(new Vector3(1f, 1f, 1f), 0.25f)
                    .SetEase(Ease.InOutSine)
                    .SetAutoKill(true);
                });
            m_roundDisplay.text = (m_roundsDone + 1).ToString();
        }
        else
        {
            m_currentCounting = m_restTime;
            m_whatPhase.text = "rest";
            m_roundsDone++;
        }
        m_audioManager.PlaySoundByIndex(0);
        m_isResting = !m_isResting;
    }
}
