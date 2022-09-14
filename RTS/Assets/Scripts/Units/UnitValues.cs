using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "New Unit", menuName = "Unit")]
public class UnitValues : ScriptableObject
{
    public int m_hp;
    public int m_range;
    public int m_moveSpeed;
}
