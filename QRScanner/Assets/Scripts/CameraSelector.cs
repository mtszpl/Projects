using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

public class CameraSelector : MonoBehaviour
{
    [SerializeField] QrScanner scanner;
    [SerializeField] Canvas choiceCanvas;
    [SerializeField] Canvas scannerCanvas;
    [SerializeField] Image parentImage;

    [SerializeField] private Transform cameraContainerTemplate;
    [SerializeField] float defaultContainerYSize = 100;
    float containerYSize = 0;

    WebCamDevice[] cameras;
    List<CameraContainer> cameraList;

    public UnityAction cameraSelected;
    public UnityAction<int> cameraSelectedInt;

    void Awake(){
        cameraSelected += DisableChoiceScreen;
        cameraSelectedInt += SelectCamera;
        cameraList = new List<CameraContainer>();
    }

    private void Start(){
        containerYSize = cameraContainerTemplate.GetComponent<RectTransform>().sizeDelta.y;
        FindCameras();
    }

    void FindCameras()
    {
        cameras = WebCamTexture.devices;
        int y = 0;
        if(containerYSize == 0)
        {
            containerYSize = defaultContainerYSize;
        }

        foreach (WebCamDevice camera in cameras)
        {
            //if (camera.isFrontFacing)
            {
                
                CameraContainer toAdd =
                    Instantiate(cameraContainerTemplate,
                    new Vector2(0, y * containerYSize),
                    Quaternion.identity)
                    .GetComponent<CameraContainer>();
                toAdd.Setup(y, camera, cameraSelected, cameraSelectedInt);
                cameraList.Add(toAdd);
                RectTransform newCameraSlot = toAdd.GetComponent<RectTransform>();
                SetSlot(newCameraSlot, y);
                y++;
            }
        }
    }

    void SetSlot(RectTransform slot, int number){
        slot.transform.SetParent(parentImage.transform);
        slot.localScale = new Vector3(1, 1, 1);
        slot.gameObject.SetActive(true);
        slot.anchoredPosition = new Vector2(0, number * containerYSize);
    }
    void SelectCamera(int id){
        scanner.SetCameraUp(cameraList[id].containedCamera);
    }

    public void DisableChoiceScreen(){
        choiceCanvas.gameObject.SetActive(false);
        scannerCanvas.gameObject.SetActive(true);
    }

    public void EnableChoiceScreen(){
        choiceCanvas.gameObject.SetActive(true);
        scannerCanvas.gameObject.SetActive(false);
        scanner.UnsetCamera();
    }

}
