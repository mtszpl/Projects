using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Engineer : Unit
{
    struct BuildPlace
    {
        public Building m_building;
        public Vector3 m_placing;
        public BuildPlace(Building building, Vector3 place)
        {
            m_building = building;
            m_placing = place;
        }
    }

    [SerializeField] List<SelectableEntity> m_possibleBuildings;
    Queue<BuildPlace> m_constructionQueue;
    BuildPlace m_currentConstruction;

    EngineerUI m_actualInterface;
    bool m_isConstructing = false;

    //Debug
    [SerializeField] UnityEngine.UI.Image image;

    public override void Init()
    {
        base.Init();
        m_constructionQueue = new Queue<BuildPlace>();
        UnitDispatcher.SetConstructableBuildings(out m_possibleBuildings);
    }

    public override void ShowUI()
    {
        if (m_actualInterface == null)
            SpawnUI();
        m_actualInterface.SpawnBuildButtons(m_possibleBuildings);
        InputController.PlugToClose(DeleteUI);

    }

    void SpawnUI()
    {
        if (m_actualInterface == null)
            m_actualInterface = Instantiate(m_interfacePrefab, transform) as EngineerUI;
        m_actualInterface.gameObject.SetActive(true);
        m_actualInterface.image = image;
        m_actualInterface.m_parent = this;
    }

    public override void DeleteUI()
    {
        base.DeleteUI();
        if (m_actualInterface != null)
            GameObject.Destroy(m_actualInterface.gameObject);
    }

    public void StartConstruction(Building toBuild)
    {
        BuildingManager.SpawnFromAfar(toBuild, this);
    }

    public override void OnAltFire(Vector3 point)
    {
        if (m_isConstructing)
            return;
        base.OnAltFire(point);
    }

    public void AddToConstructionQueue(Building toBuild, Vector3 position)
    {
        BuildPlace buildPlace = new BuildPlace(toBuild, position);
        m_constructionQueue.Enqueue(buildPlace);
        if(m_constructionQueue.Count == 1 && m_isConstructing == false)
            StartConstructionProcess();
    }

    public void ConstructionCancelled()
    {
        m_isConstructing = false;
    }

    void StartConstructionProcess()
    {
        m_isConstructing = true;
        m_currentConstruction = m_constructionQueue.Dequeue();
        SetGoal(m_currentConstruction.m_placing, m_range);
        m_onGoalReached.AddListener(StartConstructing);
    }

    public void StartConstructing()
    {
        m_isConstructing = true;
        Building construction =  Instantiate(
            m_currentConstruction.m_building,
            m_currentConstruction.m_placing,
            Quaternion.Euler(0, 0, 0));
        construction.m_parent = this;
        m_onGoalReached.RemoveListener(StartConstructing);
    }

    public void FinishContruction()
    {
        m_isConstructing = false;
        if (m_constructionQueue.Count > 0)
            StartConstructionProcess();
    }
}
