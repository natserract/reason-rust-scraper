
open Css;

module Style = {
    let layoutContainer = style([
        maxWidth(`rem(37.0)),
        margin2(`px(0), `auto),
        position(`relative),
        height(`vh(100.0)),
    ])
}

[@react.component]
let make = (~children) => {
    <div className=Style.layoutContainer>
        children
    </div>
};
