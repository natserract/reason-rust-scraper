/* access DOM */
[@bs.val] external document: Js.t({..}) = "document";

/* print string */
let str: string => React.element = React.string;
