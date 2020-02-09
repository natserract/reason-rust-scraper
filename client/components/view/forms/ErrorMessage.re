
open Css;

module Style = {
    let errorMessageStyle = style([
        color(`rgb(224, 122, 122)),
        padding2(`rem(0.5), `px(0)),
    ]);
};

[@react.component]
let make = (~children) => {
    <div className=Style.errorMessageStyle>
        children
    </div>
}