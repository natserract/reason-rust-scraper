open Utils;

let deepStyle = ReactDOMRe.Style.make(
    ~background="#e0e0e0",
    ~height="300px",
    ()
);

[@react.component]
let make = () => {
    <div name="submit-project" id="get-quote" style=deepStyle>
        <div className="src__Box-sc">
            <h2 className="text__H2">
                <span>(str("Submit your project"))</span>
            </h2>
        </div>

        <div className="src__Box-sc">
            <form name="scrapper-form">
                <div className="scrapper-form__container">
                    <div className="field-group">
                        <label>
                            <span className="label__StyledSpan">
                                (str("Project name"))
                            </span>
                        </label>
                        <input type_="text" name="title" placeholder="Example.com scraper" className="field__Style"/>
                    </div>
                    <div className="field-group">
                        <label>
                            <span className="label__StyledSpan">
                                (str("Detailed description"))
                            </span>
                        </label>
                        <textarea name="description" type_="textarea" rows=5 placeholder="Please describe all steps of the web scraping or automation process as if you were explaining them to a person who would do them manually." className="Field__StyledField-sc-1lz3ey8-0 mbzLe form-control"></textarea>
                    </div>
                    <button type_="button" className="Button__Secondary-gzupfd-1 blXtda">(str("Continue"))</button>
                </div>
            </form>
        </div>
    </div>
};