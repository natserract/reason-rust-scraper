
open Utils;
open DetailStyles;

type state = 
  | Loading
  | Loaded(Models.client);

type action = 
  | Fetch
  | Fetched(Models.client);

[@react.component]
let make = (~id: string) => {
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
                | Loaded(scraps) => {
                    <div>
                        <div className=Style.groupping>
                            <label>(str("Site Name:"))</label>
                            <pre>
                                <code>(str(scraps.site_name))</code>
                            </pre>
                        </div>
                        <div className=Style.groupping>
                            <label>(str("Description:"))</label>
                            <pre>
                                <code>(str(scraps.description))</code>
                            </pre>
                        </div>
                        <div className=Style.groupping>
                            <label>(str("Headers:"))</label>
                            <pre className="json-editor-blackbord">
                                <code>(scraps.headers -> React.string)</code>
                            </pre>
                        </div>
                        <div className=Style.groupping>
                            <label>(str("IP Address:"))</label>
                            <pre>
                                <code>(scraps.ip_address -> React.string)</code>
                            </pre>
                        </div>
                        <div className=Style.groupping>
                            <label>(str("HTML Raw:"))</label>
                            <pre className="prettyprint lang-html">
                                <code>(scraps.html_code -> React.string)</code>
                            </pre>
                        </div>
                        <div className=Style.groupping>
                            <label>(str("All Links:"))</label>
                            <pre>
                                <code>(scraps.all_links -> React.string)</code>
                            </pre>
                        </div>
                        <div className=Style.groupping>
                            <label>(str("Images:"))</label>
                            <pre>
                                <code>(scraps.images -> React.string)</code>
                            </pre>
                        </div>
                    </div>
                }
            };
        }
    </div> 
}