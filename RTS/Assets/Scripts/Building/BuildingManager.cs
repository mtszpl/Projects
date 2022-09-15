using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.EventSystems;

public class BuildingManager : IInputReceiver
{
    static BuildingManager m_instance;
    bool m_buildingMode = false;
    Building m_currentlyBuilt;
    Ghost m_currentlyBuiltGhost;

    [SerializeField] LayerMask m_terrain;
    [SerializeField] LayerMask m_noHit;
    [SerializeField] Camera m_playerCamera;

    UnityEvent<Building, Vector3> m_constructionStarted;
    UnityEvent m_constructionCancelled;

    private void Awake()
    {
        m_instance = this;
        m_constructionStarted = new UnityEvent<Building, Vector3>();
        m_constructionCancelled = new UnityEvent();
    }

    public static void SpawnFromAfar(Building toBuild, Engineer constructor)
    {
        m_instance.CreateGhost(toBuild);
        m_instance.m_constructionStarted.AddListener(constructor.AddToConstructionQueue);
        //m_instance.m_constructionCancelled.AddListener(constructor.ConstructionCancelled);
    }

    public void CreateGhost(Building toBuild)
    {
        if (m_buildingMode)
            ResetState();
        m_buildingMode = true;

        m_currentlyBuilt = toBuild;
        m_currentlyBuiltGhost = Instantiate(m_currentlyBuilt.m_ghost, new Vector3(-999, -999, -999), Quaternion.Euler(0, 0, 0));
        InputController.PlugToFire(Build);
        InputController.PlugToAltFire(ResetState);
        StartCoroutine(FollowCorsor());
    }

    void ResetState(int input)
    {
        ResetState();
        InputController.UnplugFromAltFire(ResetState);
    }

    void ResetState()
    {
        m_buildingMode = false;
        if (m_currentlyBuiltGhost != null)
        {
            GameObject.Destroy(m_currentlyBuiltGhost.gameObject);
            m_currentlyBuiltGhost = null;
        }

        InputController.UnplugFromFire(Build);
        StopAllCoroutines();
        m_constructionCancelled.Invoke();
        m_constructionStarted.RemoveAllListeners();
        m_constructionCancelled.RemoveAllListeners();
    }

    void Build(int input)
    {
        if (EventSystem.current.IsPointerOverGameObject())
            return;
        Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, m_terrain))
        {
            if (m_currentlyBuiltGhost.CheckBuildPlace())
            {
                m_constructionStarted.Invoke(m_currentlyBuilt, hit.point);
                m_constructionStarted.RemoveAllListeners();
                m_constructionCancelled.RemoveAllListeners();
                GameObject.Destroy(m_currentlyBuiltGhost.gameObject);
                m_currentlyBuilt = null;
                m_currentlyBuiltGhost = null;
                m_buildingMode = false;
            }
        }
        InputController.UnplugFromFire(Build);
    }

    IEnumerator FollowCorsor()
    {
        while(m_buildingMode)
        {
            Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;            
            if (Physics.Raycast(ray, out hit, Mathf.Infinity, m_terrain))
            {
                m_currentlyBuiltGhost.transform.position = hit.point;
                m_currentlyBuiltGhost.SnapToGrid();
            }
            yield return null;            
        }
        yield break;
    }
}
