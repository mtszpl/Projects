using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Entity : MonoBehaviour
{
    protected Transform m_mesh;

    public virtual void Init()
    {
        m_mesh = gameObject.GetComponentInChildren<Transform>();
    }
}
