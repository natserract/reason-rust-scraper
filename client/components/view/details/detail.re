
open Utils;
open DetailStyles;

type state = 
  | Loading
  | Loaded(Models.client);

type action = 
  | Fetch
  | Fetched(Models.client);

[@react.component]
let make = (~id: string=?) => {
    let (state, dispatch) = React.useReducer(
        (_state, action) => {
            switch action {
                | Fetch => Loading
                | Fetched(client)=> Loaded(client)
            };
        },
        Loading
    );

    React.useEffect0(() => {
        Js.Promise.(
            Models.API.fetch(id)
            |> then_(json => json |> client => dispatch(Fetched(client)) |> resolve )
            |> catch(_err => Js.log("Error") |> resolve)
            |> ignore
        )
        None;
    });

    <div className=Style.container>
        {
            switch state {
                | Loading => React.string("Loading") 
                | Loaded(scraps) => 
                    <div>(str(scraps.description))</div>
                
            };
        }
    </div> 
}