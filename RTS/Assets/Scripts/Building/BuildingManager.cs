using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class BuildingManager : IInputReceiver
{
    static BuildingManager m_instance;
    bool m_buildingMode = false;
    Ghost m_currentlyBuilt;

    [SerializeField] LayerMask m_terrain;
    [SerializeField] LayerMask m_noHit;
    [SerializeField] Camera m_playerCamera;
    private void Awake()
    {
        m_instance = this;
    }

    public static void SpawnFromAfar(Ghost toBuild)
    {
        m_instance.CreateGhost(toBuild);
    }

    public void CreateGhost(Ghost toBuild)
    {
        if(m_buildingMode)
            ResetState();
        m_buildingMode = true;
        Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, Mathf.Infinity))
        {
            InputController.PlugToFire(Build);
            InputController.PlugToAltFire(ResetState);
            m_currentlyBuilt = Instantiate(toBuild, hit.point, Quaternion.Euler(0, 0, 0));
            StartCoroutine(FollowCorsor());
        }
    }

    void ResetState(int input)
    {
        ResetState();
        InputController.UnplugFromAltFire(ResetState);
    }

    void ResetState()
    {
        m_buildingMode = false;
        if (m_currentlyBuilt != null)
        {
            GameObject.Destroy(m_currentlyBuilt.gameObject);
            m_currentlyBuilt = null;
        }

        InputController.UnplugFromFire(Build);

        StopAllCoroutines();
    }

    void Build(int input)
    {
        if (EventSystem.current.IsPointerOverGameObject())
            return;
        Ray ray = m_playerCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, m_terrain))
        {
            if (m_currentlyBuilt.BuildAndVanish())
            {
                m_currentlyBuilt = null;
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
                m_currentlyBuilt.transform.position = hit.point;
                m_currentlyBuilt.SnapToGrid();
            }
            yield return null;            
        }
        yield break;
    }
}
