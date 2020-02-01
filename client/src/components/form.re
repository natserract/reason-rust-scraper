
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

type state = 
  | LoadingScraps
  | ErrorFetchingScraps
  | LoadedScraps(Js.Json.t);

[@react.component]
let make = () => {
    let (state, setState) = React.useState(() => LoadingScraps);

    React.useEffect0(() => {
        Js.Promise.(
            fetch("http://localhost:4000/api/scraps")
            |> then_(response => response##json())
            |> then_(jsonResponse => {
                setState(_ => LoadedScraps(jsonResponse##data));
                Js.Promise.resolve();
            })
            |> catch(_ => {
                setState(_ => ErrorFetchingScraps);
                Js.Promise.resolve();
            })
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
      {switch state {
            | ErrorFetchingScraps => React.string("Error!!!!")
            | LoadingScraps => React.string("Loading...")
            | LoadedScraps(scraps) => 
                <div>
                    (React.string(Js.Json.stringify(scraps)))
                </div>
                
      }}
      </div>
}