
open Css;

module Style = {
    let container = style([
        paddingTop(`px(160)),
        paddingBottom(`px(110)),
        margin2(`px(0), `auto),
        maxWidth(`px(920)),
    ]);

    let groupping = style([
        marginBottom(`px(35)),

        selector(
            "label", [
                color(`hex("000")),
                fontStyle(`italic),
                fontSize(`px(15)),
            ]
        ),
        
        selector(
            "pre", [
                whiteSpace(`preLine),
                fontSize(`px(19)),

                selector(
                    "&.lang-html", [
                        height(`px(500)),
                        overflow(`scroll),
                        borderWidth(`px(0))
                    ]
                ),

                selector(
                    "code", [
                        display(`block),
                        overflow(`auto),
                        lineHeight(`em(1.5)),
                    ]
                )
            ]
        )
    ])
}