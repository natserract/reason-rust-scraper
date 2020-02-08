
open Utils;
open Models;

type state = 
  | LoadingScraps
  | ErrorFetchingScraps
  | LoadedScraps(client_array);

type action = 
  | ScrapFetch
  | ScrapFetched(client_array)
  | ScrapFailedToFetch;


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
            API.fetchAll()
            |> then_(json => json  |> scraps => dispatch(ScrapFetched(scraps)) |> resolve )
            |> catch(_err => Js.Promise.resolve(dispatch(ScrapFailedToFetch)))
            |> ignore
        )
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
                scraps.results
                -> Belt.Array.map(scrap => {
                    <pre className="prettyprint lang-html" style={ReactDOMRe.Style.make(~width="50%", ~height="50%", ())} key=(string_of_int(scrap.id))>{str(scrap.site_name)}</pre>;
                })
                -> React.array             
                
      }}
      </div>
}