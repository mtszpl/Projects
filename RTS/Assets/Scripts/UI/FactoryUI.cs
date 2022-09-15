using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FactoryUI : EntityUI
{
    [SerializeField] Button m_constructionButton;
    [SerializeField] List<Unit> m_possibilities = new List<Unit>();

    [Header("Debug")]
    [SerializeField] public Image image;

    //Debug constructor
    FactoryUI(Button buttonPrefab, List<Unit> newBuildOptions, Image newImage)
    {
        m_constructionButton = buttonPrefab;
        m_possibilities = newBuildOptions;
        image = newImage;
    }

    public override void Init()
    {
        //add read units from file
    }

    public void SpawnBuildButtons(List<Unit> newPossibilities)
    {
        m_possibilities = newPossibilities;

        foreach (Unit unit in m_possibilities)
        {
            Button newButton = Instantiate(m_constructionButton, m_bottomBox);
            newButton.image = image;
            newButton.transform.localScale = Vector3.one;
            newButton.onClick.AddListener(delegate { SpawnFromOption(unit); });
            newButton.gameObject.SetActive(true);
        }
    }

    public void SetPossibilities(List<Unit> newPossibilities)
    {
        m_possibilities = newPossibilities;
    }

    void SpawnFromOption(Unit toSpawn)
    {
        Factory parentFactory = (Factory)m_parent;
        if (parentFactory != null)
            parentFactory.AddToConstructionQueue(toSpawn);
        
    }
}
