using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Building : SelectableEntity
{
    public Engineer m_parent;
    [SerializeField] public Ghost m_ghost;

    public override void OnConstructed()
    {
        base.OnConstructed();
        m_parent.FinishContruction();
        m_parent = null;
    }

}
