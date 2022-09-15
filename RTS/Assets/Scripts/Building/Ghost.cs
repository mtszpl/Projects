using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ghost : Entity
{
    [SerializeField] int m_gridSize;
    //[SerializeField] Building m_building;

    Collider m_collider;

    private void Awake()
    {
        m_collider = gameObject.GetComponent<Collider>();
    }

    public void SnapToGrid()
    {
        transform.position = new Vector3(
            Mathf.RoundToInt(transform.position.x/m_gridSize) * m_gridSize,
            Mathf.RoundToInt(transform.position.y / m_gridSize) * m_gridSize,
            Mathf.RoundToInt(transform.position.z / m_gridSize) * m_gridSize
            );
    }

    public bool BuildAndVanish()
    {
        if (!CheckBuildPlace())
            return false;

        //Instantiate(m_building, transform.position, transform.rotation);
        GameObject.Destroy(gameObject);
        return true;
    }

    public bool CheckBuildPlace()
    {
        Vector3 extent = new Vector3(m_gridSize/2, m_gridSize/2, 0);
        Collider[] colliders = Physics.OverlapBox(
            m_collider.transform.position,
            extent,
            transform.rotation,
            LayerMask.GetMask("BuildObstacle")
            );
        if (colliders.Length == 0)
            return true;
        else
            return false;
    }

    public void Kill()
    {
        GameObject.Destroy(gameObject);
    }
}
