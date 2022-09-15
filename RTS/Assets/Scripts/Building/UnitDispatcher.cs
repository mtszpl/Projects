using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UnitDispatcher : MonoBehaviour
{
    public static UnitDispatcher m_instance;

    [SerializeField] List<SelectableEntity> m_constructableUnits;
    [SerializeField] List<SelectableEntity> m_constructableBuilding;

    private void Awake()
    {
        m_instance = this;
    }

    public static void SetConstructableUnits(out List<SelectableEntity> newUnitList)
    {
        newUnitList = m_instance.m_constructableUnits;
    }

    public static void SetConstructableBuildings(out List<SelectableEntity> newBuildingList)
    {
        newBuildingList = m_instance.m_constructableBuilding;
    }
}
