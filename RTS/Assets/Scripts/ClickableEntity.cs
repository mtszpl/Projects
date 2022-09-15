using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using DG.Tweening;

public class ClickableEntity : Entity
{
    public bool m_isConstructed;
    bool m_showingUI = false;
    public bool m_isSelected = false;

    [SerializeField] protected EntityUI m_interfacePrefab;
    protected EntityUI m_interface;

    [Header("Values")]
    [SerializeField] float m_constructionTime;
    [SerializeField] int m_hp;

    public virtual void Clone(ClickableEntity newOne)
    {
        m_interfacePrefab = newOne.m_interfacePrefab;
        m_interface = newOne.m_interface;
        m_constructionTime = newOne.m_constructionTime;
        m_hp = newOne.m_hp;
    }

    private void Awake()
    {
        Init();                   
    }

    public override void Init()
    {
        base.Init();
        m_isConstructed = true;
        m_mesh.localScale = new Vector3(1, 0, 1);
        m_mesh.transform.DOScaleY(1, m_constructionTime).OnComplete(() =>{ m_isConstructed = false; OnConstructed(); });
        m_interfacePrefab.gameObject.SetActive(false);
    }

    public virtual void OnConstructed()
    {    }

    public virtual void OnClick(out ClickableEntity clicked)
    {
        clicked = null;
        if (m_isConstructed)
            return;
        if (m_showingUI == false && !EventSystem.current.IsPointerOverGameObject())
        {
            ShowUI();
            m_isSelected = true;
            clicked = this;
        }
        else if (!EventSystem.current.IsPointerOverGameObject())
        {
            OnUnClick();
            clicked = null;
        }        
    }

    public virtual void OnAltFire(Vector3 point)
    { }

    public virtual void OnUnClick()
    {
        DeleteUI();
        m_showingUI = false;
        m_isSelected = false;
    }

    void SpawnUI()
    {
        if (m_interface == null)
            m_interface = Instantiate(m_interfacePrefab, transform);
    }

    public virtual void ShowUI()
    {
        if (m_interface == null)
            SpawnUI();
        m_interface.gameObject.SetActive(true);
        m_interface.Init();
        m_showingUI = true;
        m_interface.m_parent = this;
        InputController.PlugToClose(DeleteUI);
    }

    public virtual void ShowUI(EntityUI newInterface, out EntityUI returnUI)
    {
        if (m_interface != null)
        {
            DeleteUI();
        }
        
        returnUI = Instantiate(newInterface, transform);
        m_interface = returnUI;
        m_interface.gameObject.SetActive(true);
        m_interface.Init();
        m_showingUI = true;
    }

    public virtual void DeleteUI()
    {
        InputController.UnplugFromClose(DeleteUI);
        if (m_interface != null)
            GameObject.Destroy(m_interface.gameObject);
    }
}
