using Newtonsoft.Json;

public class ScannerIdentifier
{
    [JsonProperty("login")] string name;
    [JsonProperty("password")] string password;


    public ScannerIdentifier(string nName, string nPassword)
    {
        name = nName;
        password = nPassword;
    }

    public string Serialize()
    {
        return @JsonConvert.SerializeObject(this);
    }
}
