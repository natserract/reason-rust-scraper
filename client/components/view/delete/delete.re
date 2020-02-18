
open Utils;

[@react.component]
let make = (~id: string) => {
    React.useEffect0(() => {
        alert("This item has been sucessfully deleted");
        Js.Promise.(
            Models.API.remove(id)
            |> then_(_ => ReasonReactRouter.push("/#/data/") |> resolve)
            |> catch(err => Js.log(err) |> resolve)
            |> ignore
        )
        None;
    });

    ReasonReact.null
}