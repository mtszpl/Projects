using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.Events;

[RequireComponent(typeof(NavMeshAgent))]
public class Unit : SelectableEntity
{
    public Factory m_parent;

    [SerializeField] UnitValues m_stats;
    [SerializeField] protected float m_acceptableDistanceToTarget;
    [SerializeField] protected float m_range;

    NavMeshAgent m_agent;
    Vector3 m_goal;
    protected UnityEvent m_onGoalReached;

    public virtual void Clone(Unit otherOne)
    {
        base.Clone(otherOne);
        m_parent = otherOne.m_parent;
        m_stats = otherOne.m_stats;
        m_acceptableDistanceToTarget = otherOne.m_acceptableDistanceToTarget;
    }

    private void Start()
    {
        Init();
    }

    public override void Init()
    {
        base.Init();
        m_onGoalReached = new UnityEvent();
        if ((m_agent = gameObject.GetComponent<NavMeshAgent>()) == null)
            m_agent = gameObject.AddComponent<NavMeshAgent>();
    }

    public override void OnConstructed()
    {
        base.OnConstructed();
        m_parent.RemoveFromConstructionQueue();
        SetGoal(m_parent.m_firstWaypoint.position, m_acceptableDistanceToTarget);

        m_parent = null;
    }

    public override void OnAltFire(Vector3 point)
    {
        StopCoroutine(ResetNavigationAtEnd(m_acceptableDistanceToTarget));
        base.OnAltFire(point);
        m_agent.SetDestination(point);
        m_goal = point;
        StartCoroutine(ResetNavigationAtEnd(m_acceptableDistanceToTarget));
    }

    public void SetGoal(Vector3 newGoal, float range)
    {
        StopCoroutine(ResetNavigationAtEnd(range));
        m_goal = newGoal;
        m_agent.SetDestination(newGoal);
        StartCoroutine(ResetNavigationAtEnd(range));
    }

    IEnumerator ResetNavigationAtEnd(float acceptableRange)
    {
        do
        {
            yield return null;
        } while (Vector3.Distance(transform.position, m_goal) > acceptableRange);
        m_agent.ResetPath();
        m_onGoalReached.Invoke();
    }
}

