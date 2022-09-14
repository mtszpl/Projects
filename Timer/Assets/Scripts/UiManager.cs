using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using DG.Tweening;

public class UiManager : MonoBehaviour
{
    [SerializeField] TMP_InputField m_rounds;
    [SerializeField] TMP_InputField m_work;
    [SerializeField] TMP_InputField m_rest;

    [SerializeField] TMP_Text m_roundDisplay;
    [SerializeField] TMP_Text m_remainingDisplay;
    [SerializeField] TMP_Text m_whatPhase;
    [SerializeField] TMP_Text m_totalTime;

    public void UpdateTotalTime()
    {
        return;
        Vector3Int vals = GetAllValues();
        if (vals.x == null)
            vals.x = 0;
        if (vals.y == null)
            vals.y = 0;
        if (vals.z == null)
            vals.z = 0;
        m_totalTime.text = (vals.x * vals.z + vals.y * (vals.z - 2)).ToString();
    }

    public int GetWorkTime()
    {
        return int.Parse(m_work.text);
    }
    public int GetRestTime()
    {
        return int.Parse(m_rest.text);
    }
    public int GetRounds()
    {
        return int.Parse(m_rounds.text);
    }

    public Vector3Int GetAllValues()
    {
        int work = int.Parse(m_work.text);
        int rest = int.Parse(m_rest.text);
        int rounds = int.Parse(m_rounds.text);
        Vector3Int ret = new Vector3Int(work,
            rest,
            rounds
            );

        return ret;
    }

    public void SetRemainingDisplay(int value)
    {
        m_remainingDisplay.text = (value).ToString();
    }

    public void SetRoundDisplay(int value)
    {
        m_roundDisplay.text = (value + 1).ToString();
    }

    public void SetWhatPhase(string text)
    {
        m_whatPhase.text = text;
    }

    public void AnimateRemainingDisplay(float time, float scale)
    {
        m_remainingDisplay.transform.DOScale(new Vector3(scale, scale, scale), time)
    .SetEase(Ease.InOutSine)
    .SetLoops(-1, LoopType.Yoyo);
    }

    public void StopAnimatingRemaining()
    {
        m_remainingDisplay.transform.DOKill();
        m_remainingDisplay.transform.localScale = Vector3.one;
    }

    public void AnimateRounds(float scale, float time)
    {
        m_roundDisplay.transform.DOScale(new Vector3(scale, scale, scale), time)
                   .SetEase(Ease.InOutSine)
                   .SetAutoKill(true)
                   .OnComplete(() => {
                       m_roundDisplay.transform.DOScale(new Vector3(1f, 1f, 1f), time)
                       .SetEase(Ease.InOutSine)
                       .SetAutoKill(true);
                   });
    }
}
