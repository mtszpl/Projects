using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(NavMeshAgent))]
public class Unit : ClickableEntity
{
    [SerializeField] UnitValues m_stats;

    NavMeshAgent m_agent;

    public override void Init()
    {
        base.Init();
        m_agent = gameObject.GetComponent<NavMeshAgent>();
    }

    public override void OnClick()
    {
        base.OnClick();
    }
}

