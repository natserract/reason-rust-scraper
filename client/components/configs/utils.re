/* access DOM */
[@bs.val] external document: Js.t({..}) = "document";

/* Alert */
[@bs.val] external alert : string => unit = "alert";

/* print string */
let str: string => React.element = React.string;

[@bs.module "../view/global/alert"] external alert: string => unit = "alert";
