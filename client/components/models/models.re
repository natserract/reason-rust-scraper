module Form = ValidateHomeForm.Make;

type t = {
    site_name: string,
    description: string,
}

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


module Response = {
    exception FetchError(Fetch.response);

    let statusOk = (response) => 
        Fetch.Response.ok(response) ? Js.Promise.resolve() : Js.Promise.reject(FetchError(response));
};

module Decode = {
    let decodeData = json => 
        Json.Decode.{
            id: json |> field("id", int),
            site_name:json |> field("site_name", string),
            description:json |> field("description", string),
            headers: json |> field("headers", string),
            ip_address: json |> field("ip_address", string),
            html_code: json |> field("html_code", string),
            all_links: json |> field("all_links", string),
            images: json |> field("images", string)
        };

    let decodeUpdateData = json => 
        Json.Decode. {
            site_name:json |> field("site_name", string),
            description:json |> field("description", string),
        };


    let decodeDataArray = json =>
        Json.Decode.{
            results: json |> field("results", array(decodeData))
        }
};

module Encode = {
    let client = field => {
        Json.Encode.(
            object_([
                ("site_name", string(field.site_name)),
                ("description", string(field.description))
            ])
        )
    }
};

module API = {
    let constantUrl = "http://localhost:4000/api";
    let fetchDatasUrl = {j|$constantUrl/scraps|j};
    let fetchDataUrl = id => {j|$constantUrl/scrap/$id|j};
    let postDataUrl = {j|$constantUrl/scraps/post|j};
    let updateDataUrl = id => {j|$constantUrl/scraps/update/$id|j};
    
    let fetch = (clientId) => {
        Js.Promise.(
            Fetch.fetch(fetchDataUrl(clientId))
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.decodeData |> resolve)
        )
    }

    let fetchUpdate = (clientId) => {
        Js.Promise.(
            Fetch.fetch(fetchDataUrl(clientId))
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.decodeUpdateData |> resolve)
        )
    }

    let fetchAll = () => {
        Js.Promise.(
            Fetch.fetch(fetchDatasUrl)
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.decodeDataArray |> resolve)
        );
    }

    let add = (client: Form.state) => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "site_name", Js.Json.string(client.site_name));
        Js.Dict.set(payload, "description", Js.Json.string(client.description));

        let body = Fetch.BodyInit.make(payload |> Js.Json.object_ |> Js.Json.stringify);
        let headers = Fetch.HeadersInit.make({"Content-Type": "application/json"});
        let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());

        Js.Promise.(
            Fetch.fetchWithInit(postDataUrl, request)
            |> then_(Fetch.Response.json)
            |> then_((json) => json |> Decode.decodeData |> resolve)
        )
    } 

    let update = (id, client:t) => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "site_name", Js.Json.string(client.site_name));
        Js.Dict.set(payload, "description", Js.Json.string(client.description));

        let body = Fetch.BodyInit.make(payload |> Js.Json.object_ |> Js.Json.stringify);
        let headers = Fetch.HeadersInit.make({
            "Content-Type": "application/json; charset=UTF-8",
            "Accept": "application/json"
        });
        let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());

        Js.Promise.(
            Fetch.fetchWithInit(updateDataUrl(id), request)
            |> then_(Response.statusOk)
        )
    } 


    let remove = (clientId) => {
        let request = Fetch.RequestInit.make(~method_=Delete, ());
        Js.Promise.(
            Fetch.fetchWithInit(fetchDataUrl(clientId), request)
            |> then_(Response.statusOk)
        )
    }
}