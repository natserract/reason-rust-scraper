/* type r = {
    id: option(int),
    site_name: string,
    description: string,
};

/* module Request = {
    let defaultHeaders = [%bs.raw {|
        { "Content-Type": "application/json"}    
    |}];

    let getHeaders = () => 
        Fetch.HeadersInit.make(defaultHeaders);
};

exception FetchError(Fetch.response);

module Response = {
    let statusOk = (res) =>
        Fetch.Response.ok(res) ? Js.Promise.resolve() : Js.Promise.reject(FetchError(res));
}; */

/* receive */
module Decode = {
    let data = (json) => 
        Json.Decode.{
            id: json |> optional(field("id", int)), 
            site_name: json |> field("site_name", string),
            description: json |> field("description", string)
        };
    let data_array = (json) => Json.Decode.list(data, json);
};

/* sending */
/* module Encode = {
    let data = (clientObj) => 
        Json.Encode.(
            object_([
                ( "id",
                    switch clientObj.id {
                    | Some(id) => int(id)
                    | None => null
                    }
                ),
                ( "site_name",
                    string(clientObj.site_name)
                ),
                ( "description",
                    string(clientObj.description)
                )
            ])
        )
}; */

module API = {
    let baseUrl: string = "http://localhost:4000/api";
    let clientsUrl = {j|$baseUrl/scraps|j};
    let clientUrl = id => {j|$baseUrl/scraps/post/$id|j}

    /* let fetch = (id: int) => {
        Js.Promise.(
            Fetch.fetch(clientUrl(id))
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.data |> resolve)
        );
    } */

    let fetchAll = () => {
        Js.Promise.(
            Fetch.fetch(clientsUrl)
            |> then_(Fetch.Response.json)
            |> then_(json => 
                json |> Decode.data_array |> (scraps => Some(scraps)) |> resolve
             )
            |> catch(_err => resolve(None))
        );
    }

    /* let add = (client) => {
        let body = Fetch.BodyInit.make(client |> Encode.data |> Js.Json.stringify);
        let headers = Request.getHeaders();
        let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());

        Js.Promise.(
            Fetch.fetchWithInit(clientsUrl, request) 
            |> then_(Fetch.Response.json)
            |> then_(json => json |> Decode.data |> resolve)
        );
    } */
}

 */
