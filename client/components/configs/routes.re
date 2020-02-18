
type routes = 
  |  Delete(string)
  |  Update(string)
  |  Details(string)
  |  Data
  |  Home
  |  NotFound;

let configRoutes = () => {
    let url = ReasonReactRouter.useUrl();
    let hash = url.hash |> Js.String.split("/");

    switch (hash) {
      | [| "", "delete", id |] => Delete(id)
      | [| "", "update", id |] => Update(id)
      | [| "", "detail", id |] => Details(id)
      | [| "", "data", "" |] => Data
      | [|""|] => Home
      | _ => NotFound
    };
}