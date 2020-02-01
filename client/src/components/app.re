open Utils;
open Routes;

let applyToHeadEl = document##createElement("style");
document##head##appendChild(applyToHeadEl);
applyToHeadEl##innerHTML #= AppStyles.globalStyles;

[@react.component]
let make = () => {
    let route = useRoute();

    <Fragment>
        ( switch (route) {
            | Details => <Details/>
            | _ => <Home/>
        })
    </Fragment>
};