

open Css;

module Style = {
    let header = style([
        padding2(`rem(2.0), `px(0)),
        width(`percent(100.0)),
        position(`fixed),
        zIndex(1000),
    ]);

    let headerRow = style([
        position(`relative),
        maxWidth(`px(1280)),
        margin2(`px(0), `auto),
    ]);

    let headerInner = style([
        display(`flex),
        justifyContent(`spaceBetween),
        alignItems(`center),

        selector(
            "a", [
                color(`rgb(176, 181, 185)),
                textDecoration(`none)
            ]
        )
    ]);

    let navigation = style([
        selector(
            "ul", [
                display(`flex),
                alignItems(`center),
                padding(`px(0)),

                selector(
                    "li", [
                        padding2(`px(0), `rem(1.0)),
                        listStyleType(`none),

                    ]
                )
            ]
        ),
    ])
}