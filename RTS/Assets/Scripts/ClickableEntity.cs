using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using DG.Tweening;

public class ClickableEntity : Entity
{
    public bool m_isConstructed;
    bool m_showingUI = false;
    bool m_isSelected = false;

    [SerializeField] protected EntityUI m_interfacePrefab;
    protected EntityUI m_interface;

    [Header("Values")]
    [SerializeField] float m_constructionTime;
    [SerializeField] int m_hp;


    private void Awake()
    {
        Init();                   
    }

    public override void Init()
    {
        base.Init();
        m_isConstructed = true;
        m_mesh.localScale = new Vector3(1, 0, 1);
        m_mesh.transform.DOScaleY(1, m_constructionTime).OnComplete(() => m_isConstructed = false);
        m_interfacePrefab.gameObject.SetActive(false);
    }

    public virtual void OnClick()
    {
        if (m_showingUI == false && !EventSystem.current.IsPointerOverGameObject())
        {
            ShowUI();
            m_isSelected = true;
        }
        else if (m_showingUI == true)
        {
            DeleteUI();
            OnUnClick();
        }
    }

    public virtual void OnUnClick()
    {
        m_isSelected = false;
    }

    public virtual void ShowUI()
    {
        if(m_interface == null)
            m_interface = Instantiate(m_interfacePrefab, transform);
        m_interface.gameObject.SetActive(true);
        m_interface.Init();
        m_showingUI = true;
        InputController.PlugToClose(DeleteUI);
    }

    public virtual void ShowUI(EntityUI newInterface)
    {
        if (m_interface != null)
        {
            DeleteUI();
        }
        
        m_interface = Instantiate(newInterface, transform);
        m_interface.gameObject.SetActive(true);
        m_interface.Init();
        m_showingUI = true;
    }

    void DeleteUI()
    {
        if (m_interface != null)
        {
            GameObject.Destroy(m_interface.gameObject);
            m_showingUI = false;
        }
        InputController.UnplugFromClose(DeleteUI);
    }
}
