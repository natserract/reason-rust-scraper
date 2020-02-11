

type client = {
    id: int,
    site_name: string,
    description: string,
    headers: string,
    ip_address: string,
    html_code: string,
    all_links: string,
    images: string,
}

type client_array = {
    results: array(client)
};

module Decode = {
    let decodeData = json => 
        Json.Decode.{
            id: json |> field("id", int),
            site_name:json |> field("site_name", string),
            description:json |> field("description", string),
            headers: json |> field("description", string),
            ip_address: json |> field("ip_address", string),
            html_code: json |> field("html_code", string),
            all_links: json |> field("html_code", string),
            images: json |> field("images", string)
        };

    let decodeDataArray = json =>
        Json.Decode.{
            results: json |> field("results", array(decodeData))
        }
};

module Encode = {
    let client = field => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "id", Json.Encode.int(field.id));
        Js.Dict.set(payload, "site_name", Json.Encode.string(field.site_name));
        Js.Dict.set(payload, "description", Json.Encode.string(field.description)); 

        payload |> Js.Json.object_ 
    }
};

module API = {
    let constantUrl:string = "http://localhost:4000/api";
    let fetchDatasUrl = {j|$constantUrl/scraps|j};
    let fetchDataUrl = id => {j|$constantUrl/scrap/$id|j};
    let postDataUrl = {j|$constantUrl/scraps/post|j};
    
    let fetch = (clientId) => {
        Js.Promise.(
            Fetch.fetch(fetchDataUrl(clientId))
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.decodeData |> resolve)
        )
    }

    let fetchAll = () => {
        Js.Promise.(
            Fetch.fetch(fetchDatasUrl)
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.decodeDataArray |> resolve)
        );
    }

    let add = (client) => {
        let body = Fetch.BodyInit.make(client |> Encode.client |> Js.Json.stringify);
        let headers = Fetch.HeadersInit.make({"Content-Type": "application/json"});
        let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());

        Js.Promise.(
            Fetch.fetchWithInit(postDataUrl, request)
            |> then_(Fetch.Response.json)
            |> then_((json) => json |> Decode.decodeData |> resolve)
        )

    } 

}