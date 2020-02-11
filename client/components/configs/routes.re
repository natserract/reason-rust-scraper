
type routes = 
  |  Details(string)
  |  Data
  |  Home
  |  NotFound;

let configRoutes = () => {
    let url = ReasonReactRouter.useUrl();
    let hash = url.hash |> Js.String.split("/");

    switch (hash) {
      | [| "", "detail", id |] => Details(id)
      | [| "", "data", "" |] => Data
      | [|""|] => Home
      | _ => NotFound
    };
}