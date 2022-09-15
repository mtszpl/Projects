using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ConstructionUI : EntityUI
{
    [SerializeField] Button m_constructionButton;
    [SerializeField] List<SelectableEntity> m_possibilities = new List<SelectableEntity>();

    [Header("Debug")]
    [SerializeField] public Image image;

    //Debug constructor
    //ConstructionUI(Button buttonPrefab, List<ClickableEntity> newBuildOptions, Image newImage)
    //{
    //    m_constructionButton = buttonPrefab;
    //    m_possibilities = newBuildOptions;
    //    image = newImage;
    //}

    public override void Init()
    {
        //add read units from file
    }

    public void SpawnBuildButtons(List<SelectableEntity> newPossibilities)
    {
        m_possibilities = newPossibilities;

        foreach (SelectableEntity unit in m_possibilities)
        {
            Button newButton = Instantiate(m_constructionButton, m_bottomBox);
            newButton.image = image;
            newButton.transform.localScale = Vector3.one;
            newButton.onClick.AddListener(delegate { SpawnFromOption(unit); });
            newButton.gameObject.SetActive(true);
        }
    }

    public void SetPossibilities(List<SelectableEntity> newPossibilities)
    {
        m_possibilities = newPossibilities;
    }

    public virtual void SpawnFromOption(SelectableEntity toSpawn)
    {    }
}
