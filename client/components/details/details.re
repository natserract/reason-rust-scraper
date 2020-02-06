
open Utils;
open Belt;

type data = {
    id: int,
    html_code: string,
    site_name: string,
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
            html_code:json |> field("html_code", string),
            site_name:json |> field("site_name", string),
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
            Fetch.fetch("http://localhost:4000/api/scraps")
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
                    <pre className="prettyprint lang-html" style={ReactDOMRe.Style.make(~width="50%", ~height="50%", ())} key=(string_of_int(scrap.id))>{str(scrap.html_code)}</pre>;
                })
                -> React.array             
                
      }}
      </div>
}