

type client = {
    id: int,
    site_name: string,
    description: string,
}

type client_array = {
    results: array(client)
};

module Decode = {
    let decodeData = json => 
        Json.Decode.{
            id: json |> field("id", int),
            site_name:json |> field("site_name", string),
            description:json |> field("html_code", string),
        };

    let decodeDatas = json =>
        Json.Decode.{
            results: json |> field("results", array(decodeData))
        }
};

module Encode = {
    let datas = client => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "id", Json.Encode.int(client.id));
        Js.Dict.set(payload, "site_name", Json.Encode.string(client.site_name));
        Js.Dict.set(payload, "description", Json.Encode.string(client.description)); 

        payload |> Js.Json.object_ 
    }
};

module API = {
    let constantUrl:string = "http://localhost:4000/api";
    let fetchDatasUrl = {j|$constantUrl/scraps|j};
    let postDataUrl = {j|$constantUrl/scraps/post|j};
    
    let fetchAll = () => {
        Js.Promise.(
            Fetch.fetch(fetchDatasUrl)
            |> then_(Fetch.Response.json)
            |> then_(json => json    |> Decode.decodeDatas |> resolve)
        );
    }

    let add = (client) => {
        let body = Fetch.BodyInit.make(client |> Encode.datas |> Js.Json.stringify);
        let headers = Fetch.HeadersInit.make({"Content-Type": "application/json"});
        let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());

        Js.Promise.(
            Fetch.fetchWithInit(postDataUrl, request)
            |> then_(Fetch.Response.json)
            |> then_((json) => json |> Decode.decodeData |> resolve)
        )

    } 

}