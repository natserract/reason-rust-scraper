
open Utils;
open DataStyles;

type state =
  | LoadingScraps
  | ErrorFetchingScraps
  | LoadedScraps(Models.client_array);

type action = 
  | Fetch
  | Fetched(Models.client_array)
  | FailedToFetch;

[@react.component]
let make = () => {
    let (state, dispatch) = React.useReducer(
        (_state, action) => {
            switch  action {
                | Fetch => LoadingScraps
                | Fetched(scraps) => LoadedScraps(scraps)
                | FailedToFetch => ErrorFetchingScraps
            };
        },
        LoadingScraps
    );

    React.useEffect0(() => {
        Js.Promise.(
            Models.API.fetchAll()
            |> then_(json => json |> scraps => dispatch(Fetched(scraps)) |> resolve )
            |> catch(_err => Js.Promise.resolve(dispatch(FailedToFetch)))
            |> ignore
        )
        None;
    });

    let num = string_of_int(10);

    <div className=Style.container>
        {
            switch state {
                | ErrorFetchingScraps => React.string("Failed to fetch")
                | LoadingScraps => React.string("Loading")
                | LoadedScraps(scraps) => 
                    scraps.results
                    -> Belt.Array.map(scrap => {
                        let getItemID = string_of_int(scrap.id);
                        <div className=Style.item onClick={_ => ReasonReactRouter.push({j|/#/detail/$getItemID|j})} key=(string_of_int(scrap.id))>
                            <h4 className=Style.title>(str(scrap.site_name))</h4>
                            <p className=Style.description>(str(scrap.description))</p>
                            <div className=Style.inner>
                                <a href="/">(str("Update"))</a>
                                <a href="/">(str("Delete"))</a>
                            </div>
                        </div>
                    })
                    -> React.array
            };
        }
    </div>
}