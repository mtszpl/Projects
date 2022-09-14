using Newtonsoft.Json;

public class Ticket
{
    [JsonProperty("code")] string code;

    public Ticket(string nCode)
    {
        code = nCode;
    }

    public string Serialize()
    {
        return JsonConvert.SerializeObject(this);
    }
}
