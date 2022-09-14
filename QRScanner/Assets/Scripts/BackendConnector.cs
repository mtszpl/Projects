using System.Text;
using System.Collections;
using UnityEngine;
using UnityEngine.Networking;
using Newtonsoft.Json;

public class BackendConnector : MonoBehaviour
{
    [SerializeField] string uri = "http://projekt-pp-tab-2022.herokuapp.com/api";
    ScannerIdentifier scannerIdentifier;
    AuthorizationData authorizationData;
    bool isAuthorised;

    private void Awake()
    {
        scannerIdentifier = new ScannerIdentifier("scanner1", "scanner1password");
        string authUri = uri + "/scanner/login";
        StartCoroutine(SendLogin(authUri));
    }

    IEnumerator SendLogin(string authUri)
    {
        string packed = scannerIdentifier.Serialize();
        byte[] encoded = Encoding.UTF8.GetBytes(packed);

        UnityWebRequest request = UnityWebRequest.Post(authUri, scannerIdentifier.Serialize());
        request.SetRequestHeader("Content-Type", "application/json");
        request.uploadHandler = new UploadHandlerRaw(encoded);

        yield return request.SendWebRequest();
        if (request.result == UnityWebRequest.Result.Success)
        {
            authorizationData = JsonConvert.DeserializeObject<AuthorizationData>( request.downloadHandler.text);
            isAuthorised = true;
        }
        else
            isAuthorised = false;
    }

    public bool CheckScanCorrectness(string scan)
    {
        if (!isAuthorised)
            return false;
        //StartCoroutine(SendScan(scan));
        return scanFunction(scan);
    }

    bool scanFunction(string scan)
    {
        string scanUri = uri + "/scan";
        Ticket ticket = new Ticket(scan);
        string packed = ticket.Serialize();
        byte[] encoded = Encoding.UTF8.GetBytes(packed);

        UnityWebRequest request = UnityWebRequest.Post(scanUri, packed);
        request.SetRequestHeader("Authorization", "Bearer " + authorizationData.accessToken);
        request.SetRequestHeader("Content-Type", "application/json");
        request.uploadHandler = new UploadHandlerRaw(encoded);

        request.SendWebRequest();
        while (!request.isDone)
            ;
        if (request.result == UnityWebRequest.Result.Success)
            return true;
        else
            return false;
    }

}
