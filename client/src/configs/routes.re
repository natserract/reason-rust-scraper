
type routes = 
  |  Details
  |  Home;

let useRoute = () => {
    let url = ReasonReactRouter.useUrl();
    let hash = url.hash |> Js.String.split("/");

    switch (hash) {
      | [| "", "detail", "" |] => Details
      | _ => Home
    };
}