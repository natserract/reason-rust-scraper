
open Utils;
open HomeStyles;

module Form = ValidateHomeForm.Make;
module FormHook = Formality.Async.Make(Form);

let initialState = 
    Form.{ 
        site_name: "", 
        description: ""
    };

[@react.component]
let make = () => {
    let form = 
        FormHook.useForm(
            ~initialState,
            ~onSubmit=(state, form) => {
                Js.Promise.(
                    Models.API.add(state)
                    |> then_(_ => {
                        form.notifyOnSuccess(None);
                        form.reset->Js.Global.setTimeout(1000)->ignore;
                        resolve();
                    })
                    |> catch(_err => {
                        form.notifyOnFailure(Js.log("Error"));
                        resolve();
                    })
                    |> ignore
                );
            },
        );
    
        <Container>
            <CenterPosition>
                <h2 className=Styles.heading>(str("Submit Your Site"))</h2>
                <form className=Styles.form onSubmit={form.submit->Formality.Dom.preventDefault}>
                <div className="field-title">
                    <label>"Site Name:" -> React.string</label>
                    <input
                        type_="text"
                        value={form.state.site_name}
                        disabled={form.submitting}
                        placeholder="Example.com scraper (https/http)"
                        onBlur={_ => form.blur(SiteName)}
                        onChange={event => 
                            form.change(
                                SiteName,
                                Form.SiteNameField.update(
                                    form.state,
                                    event -> ReactEvent.Form.target##value,
                                )
                            )
                        }
                    />
                    { switch (SiteName->(form.result)) {
                        | Some(Error(err)) => <ErrorMessage>(str(err))</ErrorMessage>
                        | Some(Ok(Valid)) => React.null
                        | Some(Ok(NoValue)) | None => React.null
                    }}
                </div>
        
                <div className="field-description">
                    <label>"Detailed Description:" -> React.string</label>
                        <textarea
                            type_="text"
                            value={form.state.description}
                            disabled={form.submitting}
                            placeholder="Please describe all steps of the web scraping or automation process as if you were explaining them to a person who would do them manually."
                            onBlur={_ => form.blur(Description)}
                            onChange={event => 
                                form.change(
                                    Description,
                                    Form.DescField.update(
                                        form.state,
                                        event -> ReactEvent.Form.target##value,
                                    )
                                )
                            }>{str(form.state.description)}</textarea>
                        { switch (Description->(form.result)) {
                            | Some(Error(err)) => <ErrorMessage>(str(err))</ErrorMessage>
                            | Some(Ok(Valid)) => React.null
                            | Some(Ok(NoValue)) | None => React.null
                        }}
                </div>
                <button className=Styles.button disabled={form.submitting}>
                        (form.submitting ? "Submitting..." : "Submit") -> React.string
                </button>
                {switch (form.status) {
                    | Submitted => 
                        <span style=(ReactDOMRe.Style.make(
                            ~color="#a5d2b3", 
                            ~display="block", 
                            ~marginTop="20px", 
                        ()))> (str("Well done!")) </span>
                    | _ => React.null
                    }}
            </form>
            <span style=(ReactDOMRe.Style.make(
                ~textAlign="center", 
                ~display="block",
                ~marginTop="30px",
                ~color="#c1c1c1",
                ()
            ))>"Why scrapping not work?" -> str 
            <a style=(ReactDOMRe.Style.make(
                ~color="#c1c1c1",
            ())) href="https://www.scrapehero.com/how-to-prevent-getting-blacklisted-while-scraping/" target="_blank">" Read this" -> str</a></span>
        </CenterPosition>
    </Container>
}