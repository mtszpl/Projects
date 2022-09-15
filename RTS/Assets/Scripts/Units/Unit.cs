using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(NavMeshAgent))]
public class Unit : ClickableEntity
{
    public Factory m_parent;

    [SerializeField] UnitValues m_stats;
    [SerializeField] float m_acceptableDistanceToTarget;

    NavMeshAgent m_agent;
    Vector3 m_goal;

    public virtual void Clone(Unit otherOne)
    {
        base.Clone(otherOne);
        m_parent = otherOne.m_parent;
        m_stats = otherOne.m_stats;
        m_acceptableDistanceToTarget = otherOne.m_acceptableDistanceToTarget;
    }

    private void Awake()
    {
        if ((m_agent = gameObject.GetComponent<NavMeshAgent>()) == null)
            m_agent = gameObject.AddComponent<NavMeshAgent>();
    }

    private void Update()
    {
        if (Vector3.Distance(transform.position, m_goal) < m_acceptableDistanceToTarget)
            m_agent.ResetPath();
    }

    public override void Init()
    {
        base.Init();
    }

    public override void OnConstructed()
    {
        base.OnConstructed();
        m_parent.RemoveFromConstructionQueue(this);
        SetGoal(m_parent.m_firstWaypoint.position);
    }

    public override void OnAltFire(Vector3 point)
    {
        base.OnAltFire(point);
        m_agent.SetDestination(point);
        m_goal = point;
    }

    public void SetGoal(Vector3 newGoal)
    {
        m_goal = newGoal;
        m_agent.SetDestination(newGoal);
    }

    //public override void 
}

