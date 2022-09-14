using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Factory : Building
{
    List<Entity> m_buildQueue;

    public override void ShowUI()
    {
        base.ShowUI();
        m_interface.m_parent = this;
    }
}
