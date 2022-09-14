using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FactoryUI : EntityUI
{
    [SerializeField] Button m_constructionButton;
    [SerializeField] List<Entity> m_possibilities = new List<Entity>();

    [Header("Debug")]
    [SerializeField] Image image;


    public override void Init()
    {
        
    }

    public void SpawnBuildButtons(List<Entity> newPossibilities)
    {
        m_possibilities = newPossibilities;

        foreach (Entity unit in m_possibilities)
        {
            Button newButton = Instantiate(m_constructionButton, m_bottomBox);
            Debug.Log(newButton.transform.name);
            newButton.image = image;
            newButton.onClick.AddListener(delegate { SpawnFromOption(unit); });
        }
    }

    void SpawnFromOption(Entity toSpawn)
    {
        BuildingManager.SpawnFromAfar((Ghost)toSpawn);
    }
}
