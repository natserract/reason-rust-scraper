
open Css;

module Style = {
    let container = style([
        paddingTop(`px(160)),
        paddingBottom(`px(110)),
        margin2(`px(0), `auto),
        maxWidth(`px(920)),
    ]);

    let item = style([
        padding2(`rem(2.5), `rem(4.0)),
        background(`rgb(255, 255, 255)),
        marginBottom(`rem(1.6)),
        borderRadius(`rem(0.4)),
        display(`block),
        boxShadows([
            Shadow.box(~blur=rem(0.4), `rgba(158, 164, 168, 0.3)),
            Shadow.box(~y=rem(0.4), ~blur=rem(1.4), `rgba(158, 164, 168, 0.3)),
        ]),
        textDecoration(`none)
    ]);

    let title = style([
        fontSize(`rem(2.0)),
        cursor(`pointer),
        color(`rgb(0, 0, 0)),
        fontWeight(`lighter),
        lineHeight(`em(1.22)),
        margin4(`px(0), `px(0), `px(20), `px(0)),

        selector(
            ":hover, :focus", [
                textDecoration(`underline),
            ]
        )
    ]);

    let description = style([
        fontSize(`rem(1.0)),
        lineHeight(`em(1.5)),
        color(`rgb(139, 148, 155)),
    ]);

    let inner = style([
        display(`flex),
        marginTop(`px(30)),

        selector(
            "a", [
                color(`rgb(18, 172, 241)),
                background(`rgba(13, 156, 220, 0.1)),
                padding2(`rem(0.5), `rem(2.0)),
                transition(~duration=300, ~timingFunction=easeInOut, "all"),
                fontWeight(`medium),
                borderRadius(`rem(0.5)),
                border(`px(0), none, `transparent),
                cursor(`pointer),
                fontSize(`px(16)),
                position(`relative),
                display(`inlineBlock),
                top(`rem(0.0)),
                textDecoration(`none),
                marginRight(`px(10)),

                selector(
                    ":hover, :focus", [
                        background(`rgba(13, 156, 220, 0.2)),
                        top(`rem(-0.3)),
                    ]
                ),
                
                selector(
                    "&:nth-child(2)", [
                        background(`rgb(255, 231, 231)),
                        color(`rgb(212, 127, 146)),

                        selector(
                            ":hover, :focus", [
                                background(`rgb(251, 217, 217)),
                                top(`rem(-0.3)),
                            ]
                        ),
                    ]
                )
            ]
        )
    ])
}