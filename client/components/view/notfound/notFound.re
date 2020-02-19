open Utils;

[@react.component]
let make = () => {
    <Container>
        <CenterPosition>
            <div style=(ReactDOMRe.Style.make(
                ~textAlign="center",
                ~color="rgb(193, 193, 193)",
                ~fontSize="25px",
            ()))>(str("Oops! Page Not Found"))</div>
        </CenterPosition>
    </Container>
}