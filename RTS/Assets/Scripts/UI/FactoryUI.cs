using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FactoryUI : ConstructionUI
{
    public override void Init()
    {
        base.Init();
    }

    public override void SpawnFromOption(SelectableEntity toSpawn)
    {

        Factory parentFactory = m_parent as Factory;
        if (parentFactory != null)
            parentFactory.AddToConstructionQueue(toSpawn as Unit);
    }
}
