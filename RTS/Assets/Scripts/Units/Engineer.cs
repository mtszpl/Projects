using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Engineer : Unit
{
    [SerializeField] List<Entity> m_possibleBuilding;

    //Debug
    FactoryUI factoryUI;
    FactoryUI toInstantiate;

    private void Awake()
    {
        factoryUI = (FactoryUI)m_interfacePrefab;
    }


    public override void Init()
    {
        base.Init();
    }

    public override void ShowUI()
    {
        base.ShowUI();
    }

    public override void OnClick()
    {
        //base.OnClick();
        ShowUI(factoryUI);
        toInstantiate = m_interface as FactoryUI;
        toInstantiate.SpawnBuildButtons(m_possibleBuilding);
    }

    public override void OnUnClick()
    {
        base.OnUnClick();
        
    }
}
