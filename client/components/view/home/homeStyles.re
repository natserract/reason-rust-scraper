
open Css;

module Styles = {
    let heading = style([
        fontSize(`rem(2.5)),
        lineHeight(`em(1.17)),
        textAlign(`center),
        marginBottom(`em(1.0)),
        fontWeight(`light),
        color(`hex("10acf1")),
    ])

    let form = style([
        background(hex("fff")),
        boxShadows([
            Shadow.box(~blur=px(4), `rgba(159, 165, 169, 0.2)),
            Shadow.box(~y=px(6), ~blur=px(12),`rgba(159, 165, 169, 0.2))
        ]),
        padding2(`px(20), `px(25)),
        borderRadius(px(5)),

        selector(
            "& > div", [
                marginBottom(`px(20)),
            ]
        ),

        selector(
            "label", [
                display(`block),
                color(`rgb(132, 140, 145)),
                letterSpacing(`pxFloat(0.5)),
                marginBottom(`px(10))
            ],
        ),
        selector(
            "input, textarea", [
                color(`rgb(0, 0, 0)),
                backgroundColor(`rgb(255, 255, 255)),
                width(`percent(100.0)),
                borderRadius(`px(5)),
                padding2(`rem(0.5), `rem(0.6)),
                boxShadow(`none),
                outline(`px(0), `none, `transparent),
                border(`px(1), `solid, `rgba(159, 165, 169, 0.2)),
                boxSizing(`borderBox),
                fontSize(`px(15)),
                lineHeight(`em(1.5)),
                fontWeight(`light),

                selector(
                    "&::-webkit-input-placeholder", [
                        color(`hex("bdbdbd")),
                    ]
                ),
            ],
        ),
        selector(
            "textarea", [
                minHeight(`rem(8.0)),
            ]
        ),
        selector(
            "button[disabled]", [
                opacity(0.5)
            ]
        )
    ]);


    let button = style([
        color(`rgb(18, 172, 241)),
        background(`rgba(13, 156, 220, 0.1)),
        padding2(`rem(1.0), `rem(3.0)),
        transition(~duration=300, ~timingFunction=easeInOut, "all"),
        fontWeight(`medium),
        borderRadius(`rem(0.5)),
        border(`px(0), none, `transparent),
        cursor(`pointer),
        fontSize(`px(16)),
        position(`relative),
        display(`inlineBlock),
        top(`rem(0.0)),
        outline(`px(0), `none, `transparent),

        selector(
            ":hover, :focus", [
                background(`rgba(13, 156, 220, 0.2)),
                top(`rem(-0.3)),
            ]
        )
    ])
}