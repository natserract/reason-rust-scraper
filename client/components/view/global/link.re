
let handleClick = (href, event) => {
    if(!ReactEvent.Mouse.defaultPrevented(event)) {
        ReactEvent.Mouse.preventDefault(event);
        ReasonReactRouter.push(href);
    }
};

[@react.component]
let make = (~href, ~className="", ~target="", ~children) => {
    <a href className target onClick={e=>handleClick(href, e) }>
        children
    </a>
}