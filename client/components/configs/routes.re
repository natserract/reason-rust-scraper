
type routes = 
  |  Details
  |  Data
  |  Home
  |  NotFound;

let configRoutes = () => {
    let url = ReasonReactRouter.useUrl();
    let hash = url.hash |> Js.String.split("/");

    switch (hash) {
      | [| "", "detail", "" |] => Details
      | [| "", "data", "" |] => Data
      | [|""|] => Home
      | _ => NotFound
    };
}