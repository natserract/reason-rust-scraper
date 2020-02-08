
open Css;

module Styles = {
    let centerAlignPosition = style([
        position(`absolute),
        top(`percent(50.0)),
        left(`percent(50.0)),
        width(`percent(100.0)),
        transform(`translate(`percent(-50.0), `percent(-55.0))),
    ]);
};

[@react.component]
let make = (~children) => {
    <div className=Styles.centerAlignPosition>
        children
    </div>
}