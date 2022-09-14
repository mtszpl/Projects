using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EntityUI : MonoBehaviour
{
    public ClickableEntity m_parent;
    [SerializeField] protected RectTransform m_bottomBox;

    public virtual void Init()
    {
    }
}
