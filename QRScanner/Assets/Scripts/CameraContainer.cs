using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;
using TMPro;

public class CameraContainer : MonoBehaviour
{
    int id;
    public WebCamDevice containedCamera;
    Button button;
    UnityAction<int> setupCameraById;
    TMP_Text text;

    void OnEnable(){
        button = GetComponent<Button>();
        text = transform.GetComponentInChildren<TMP_Text>();
    }

    public void Setup(int _id, WebCamDevice _camera,
        UnityAction _setupVoid, UnityAction<int> _setupCameraById){
        id = _id;
        containedCamera = _camera;
        text.text = containedCamera.name;
        setupCameraById = _setupCameraById;
        button.onClick.AddListener(SelectById);
        button.onClick.AddListener(_setupVoid);
    }

    void SelectById(){
        setupCameraById.Invoke(id);
    }
}
