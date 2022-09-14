using System.Collections;
using UnityEngine;
using UnityEngine.UI;
using ZXing;
using TMPro;

public class QrScanner : MonoBehaviour
{
    enum Mode
    {
        Async,
        nAsync
    }

    [SerializeField] RawImage rawImageBackground;
    [SerializeField] AspectRatioFitter aspectRatioFitter;
    [SerializeField] TextMeshProUGUI outputText;
    [SerializeField] RectTransform scanZone;
    [SerializeField] float delayTime;
    [SerializeField] Mode mode;
    BackendConnector backend;
    float remainingDelay;

    bool hasCamera;
    WebCamTexture cameraScanner;

    private void Start()
    {
        backend = gameObject.GetComponent<BackendConnector>();
    }

    void Update()
    {
        UpdateCameraRender();
        if (mode == Mode.nAsync)
            UpdateTime();

    }

    public void SetCameraUp(WebCamDevice device){
            cameraScanner = new WebCamTexture(device.name,
              (int)scanZone.rect.width, (int)scanZone.rect.height);
        cameraScanner.Play();
        rawImageBackground.texture = cameraScanner;
        rawImageBackground.transform.localScale = new Vector3(-1, 1, -1);
        hasCamera = true;
        if(mode == Mode.Async)
            StartCoroutine(ScanAsync());
    }

    public void UnsetCamera(){
        cameraScanner.Stop();
        rawImageBackground.texture = null;
        hasCamera = false;
    }

    private void UpdateCameraRender(){
        if (hasCamera == false){
            return;
        }
        float ratio = (float)cameraScanner.width / (float) cameraScanner.height;
        aspectRatioFitter.aspectRatio = ratio;

        int rotation = -cameraScanner.videoRotationAngle;

        rawImageBackground.rectTransform.localEulerAngles = new Vector3(0, 0, rotation);
    }

    IEnumerator ScanAsync()
    {
        while (mode == Mode.Async)
        {
            if (!hasCamera || !cameraScanner.isPlaying)
            {
                yield break;
            }
                IBarcodeReader barcodeReader = new BarcodeReader();
                Result result = barcodeReader.Decode(cameraScanner.GetPixels32(),
                    cameraScanner.width, cameraScanner.height);
                if (result != null)
                {
                    outputText.SetText(result.Text);
                    remainingDelay = delayTime;
                    if (backend.CheckScanCorrectness(result.Text))
                    {
                        outputText.color = Color.green;
                        outputText.SetText("You can go");
                    }
                    else
                    {
                        outputText.color = Color.red;
                        outputText.SetText("You shall not pass!");
                    }
                    yield return new WaitForSecondsRealtime(delayTime);
                    outputText.color = Color.white;
                }
                else
                {
                    outputText.SetText("NO SCAN");
                    yield return new WaitForEndOfFrame();
                }
        }
    }

    private void Scan(){ 
        if(!hasCamera || !cameraScanner.isPlaying){
            return;
        }
        outputText.color = Color.white;
        try
        {
            IBarcodeReader barcodeReader = new BarcodeReader();
            Result result = barcodeReader.Decode(cameraScanner.GetPixels32(),
                cameraScanner.width, cameraScanner.height);
            if (result != null){
                outputText.SetText(result.Text);
                remainingDelay = delayTime;
                if(backend.CheckScanCorrectness(result.Text))
                {
                    outputText.color = Color.green;
                    outputText.SetText("You can go");
                }
                else
                {
                    outputText.color = Color.red;
                    outputText.SetText("You shall not pass!");
                }
            }
            else{
                outputText.SetText("NO SCAN");
            }
        }
        catch{
            outputText.SetText("SCAN FAILED");
        }
    }

    private void UpdateTime()
    {
        if (remainingDelay <= 0)
            Scan();
        else
            remainingDelay -= Time.deltaTime;
    }
}
