
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
            switch action {
                | Fetch => LoadingScraps
                | Fetched(scraps) => LoadedScraps(scraps)
                | FailedToFetch => ErrorFetchingScraps
            };
        },
        LoadingScraps
    );

    React.useEffect1(() => {
        Js.Promise.(
            Models.API.fetchAll()
            |> then_(json => json |> scraps => dispatch(Fetched(scraps)) |> resolve )
            |> catch(_err => Js.Promise.resolve(dispatch(FailedToFetch)))
            |> ignore
        )
        None;

    }, [|LoadingScraps|]);


    <div className=Style.container>
        {
            switch state {
                | ErrorFetchingScraps => React.string("Failed to fetch")
                | LoadingScraps => React.string("Loading")
                | LoadedScraps(scraps) => 
                    scraps.results
                    -> Belt.Array.map(scrap => {
                        let getItemID = string_of_int(scrap.id);
                        <div className=Style.item key=(string_of_int(scrap.id))>
                            <h4 onClick={_ => ReasonReactRouter.push({j|/#/detail/$getItemID|j})} className=Style.title>(str(scrap.site_name))</h4>
                            <p className=Style.description>(str(scrap.description))</p>
                            <div className=Style.inner>
                                <a href={j|/#/update/$getItemID|j}>(str("Update"))</a>
                                <a href={j|/#/delete/$getItemID|j}>(str("Delete"))</a>
                            </div>
                        </div>
                    })
                    -> React.array
            };
        }
    </div>
}