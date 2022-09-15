using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Factory : Building
{
    [SerializeField] List<Unit> m_buildOptions;
    [SerializeField] Transform m_buildPosition;
    [SerializeField] public Transform m_firstWaypoint;
    Queue<Unit> m_constructionQueue;
    FactoryUI m_actualInterface;
    bool m_isConstructing = false;

    //Debug
    [SerializeField] UnityEngine.UI.Image image;

    public override void Init()
    {
        base.Init();
        m_constructionQueue = new Queue<Unit>();
    }

    public override void ShowUI()
    {
        if (m_actualInterface == null)
            SpawnUI();
        m_actualInterface.SetPossibilities(m_buildOptions);
        m_actualInterface.SpawnBuildButtons(m_buildOptions);
        InputController.PlugToClose(DeleteUI);
    }

    void SpawnUI()
    {
        if (m_actualInterface == null)
            m_actualInterface = Instantiate(m_interfacePrefab, transform) as FactoryUI;
        m_actualInterface.gameObject.SetActive(true);
        m_actualInterface.image = image;
        m_actualInterface.m_parent = this;
    }

    public void AddToConstructionQueue(Unit newOne)
    {
        m_constructionQueue.Enqueue(newOne);
        if(m_isConstructing == false)
            StartConstruction(m_constructionQueue.Dequeue());
    }

    public void StartConstruction(Unit toConstruct)
    {
        m_isConstructing = true;
        Unit constructed = Instantiate(toConstruct, m_buildPosition);
        constructed.Init();
        constructed.m_parent = this;
    }

    public void RemoveFromConstructionQueue(Unit toRemove)
    {
        m_isConstructing = false;
        if (m_constructionQueue.Count > 0)
            StartConstruction(m_constructionQueue.Dequeue());
    }

    public override void DeleteUI()
    {
        base.DeleteUI();
        if (m_actualInterface != null)
            GameObject.Destroy(m_actualInterface.gameObject);
    }
}
