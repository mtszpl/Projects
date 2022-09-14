using Newtonsoft.Json;

public class AuthorizationData
{
    [JsonProperty("accessToken")]public string accessToken;
    [JsonProperty("refreshToken")]public string refreshToken;
}
