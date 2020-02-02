
open Utils;
open Belt;

type data = {
    id: int,
    body: string,
    createdAt: option(Js.Date.t),
    description: string,
    headers: string,
    site_name: string,
    updatedAt: option(Js.Date.t),
}

type datas = {
    result: array(data)
};

type state = 
  | LoadingScraps
  | ErrorFetchingScraps
  | LoadedScraps(datas);

type action = 
  | ScrapFetch
  | ScrapFetched(datas)
  | ScrapFailedToFetch;


module Decode = {
    let decodeData = json => 
        Json.Decode.{
            id: json |> field("id", int),
            body:json |> field("body", string),
            createdAt: json |> optional(field("created_at", date)),
            description: json |> field("description", string),
            headers: json |> field("headers", string),
            site_name:json |> field("site_name", string),
            updatedAt: json |> optional(field("updated_at", date))
        };

    let decodeDatas = json =>
        Json.Decode.{
            result: json |> field("result", array(decodeData))
        }
};

[@react.component]
let make = () => {
    let (state, dispatch) = React.useReducer(
        (_state, action) => 
            switch action {
                | ScrapFetch => LoadingScraps
                | ScrapFetched(scraps) => LoadedScraps(scraps)
                | ScrapFailedToFetch => ErrorFetchingScraps
            },
            LoadingScraps,
    );


    React.useEffect0(() => {
        Js.Promise.(
            Fetch.fetch("http://localhost:4000/api/scraps/")
            |> then_(Fetch.Response.json)
            |> then_(json => 
                json    |> Decode.decodeDatas
                        |> (scraps => dispatch(ScrapFetched(scraps)))
                        |> resolve
            )
            |> catch(_err => Js.Promise.resolve(dispatch(ScrapFailedToFetch)))
            |> ignore
        );

        None;
    });

    <div 
        style={ReactDOMRe.Style.make(
        ~height="120px",
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="center",
        (),
      )}>
      { switch state {
            | ErrorFetchingScraps => React.string("Error!!!!")
            | LoadingScraps => React.string("Loading...")
            | LoadedScraps(scraps) => 
                scraps.result
                -> Belt.Array.map(scrap => {
                    <li key=(string_of_int(scrap.id))>{str(scrap.site_name)}</li>;
                })
                -> React.array             
                
      }}
      </div>
}