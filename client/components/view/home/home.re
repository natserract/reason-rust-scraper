
open Utils;
open HomeStyles;

module Form = HomeForm.Make;
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
                let payload = Js.Dict.empty();
                Js.Dict.set(payload, "site_name", Js.Json.string(state.site_name));
                Js.Dict.set(payload, "description", Js.Json.string(state.description));
                
                let body = Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload)));
                let headers = Fetch.HeadersInit.make({"Content-Type": "application/json"});
                
                Js.Promise.(
                    Fetch.fetchWithInit(
                        "http://localhost:4000/api/scraps/post",
                        Fetch.RequestInit.make(
                            ~method_=Post,
                            ~body,
                            ~headers,
                            ()
                        )
                    )
                    |> then_(Fetch.Response.json)
                    |> ignore
                );
                
                Js.Global.setTimeout(
                    () => {
                        form.notifyOnSuccess(None);
                        form.reset->Js.Global.setTimeout(3000)->ignore;
                    },
                    500,
                )
                -> ignore;
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
                    <div>
                        {j|✓ Success|j}->React.string
                    </div>
                    | _ => React.null
                    }}
            </form>
        </CenterPosition>
    </Container>
}