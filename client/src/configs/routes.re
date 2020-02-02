
type routes = 
  |  Details
  |  Home
  |  NotFound;

let useRoute = () => {
    let url = ReasonReactRouter.useUrl();
    let hash = url.hash |> Js.String.split("/");

    switch (hash) {
      | [| "", "detail", "" |] => Details
      | [|""|] => Home
      | _ => NotFound
    };
}