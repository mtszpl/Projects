using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EngineerUI : ConstructionUI
{
    public override void Init()
    {
        base.Init();
    }

    public override void SpawnFromOption(SelectableEntity toSpawn)
    {
        Engineer parentEngineer = m_parent as Engineer;
        if (parentEngineer != null)
            parentEngineer.StartConstruction(toSpawn as Building);
    }
}
