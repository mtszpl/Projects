using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Engineer : Unit
{
    [SerializeField] List<Entity> m_possibleBuilding;

    //Debug
    FactoryUI factoryUI;
    FactoryUI toInstantiate;

    public override void Init()
    {
        base.Init();
    }

    public override void ShowUI()
    {
        base.ShowUI();
    }

    public override void OnClick(out ClickableEntity clicked)
    {
        base.OnClick(out clicked);
        //clicked = this;
    }

    public override void OnUnClick()
    {
        base.OnUnClick();
        
    }
}
