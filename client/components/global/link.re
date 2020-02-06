
let handleClick = (href, event) => {
    if(!ReactEvent.Mouse.defaultPrevented(event)) {
        ReactEvent.Mouse.preventDefault(event);
        ReasonReactRouter.push(href);
    }
};

[@react.component]
let make = (~href, ~className="", ~children) => {
    <a href className onClick={e=>handleClick(href, e) }>
        children
    </a>
}