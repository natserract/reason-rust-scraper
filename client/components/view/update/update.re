

open Utils;
open HomeStyles;

module Form = ValidateHomeForm.Make;
module FormHook = Formality.Async.Make(Form);

type state = 
 | Loaded(Models.t);

type action = 
 | Fetched(Models.t);


[@react.component]
let make = (~id: string) => {
    let (state, dispatch) = React.useReducer(
        (_state, action) => {
            switch action {
                | Fetched(client)=> Loaded(client)
            };
        },
        Loaded({
            site_name: "",
            description: ""
        })
    );

    React.useEffect0(() => {
        Js.Promise.(
            Models.API.fetchUpdate(id)
            |> then_(json => json |> client => dispatch(Fetched(client)) |> resolve )
            |> catch(_err => Js.log("Error") |> resolve)
            |> ignore
        )
        None;
    });

    switch state {
    | Loaded(scrap) => 
        let initialState = 
            Form.{ 
                site_name: scrap.site_name, 
                description: scrap.description
            };
        

        let form = 
            FormHook.useForm(
                ~initialState,
                ~onSubmit=(state, form) => {
                    Js.Promise.(
                        Models.API.add(state)
                        |> then_(_ => {
                            form.notifyOnSuccess(None);
                            form.reset->Js.Global.setTimeout(3000)->ignore;
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
                <h2 className=Styles.heading>(str("Update Data"))</h2>
                <form className=Styles.form onSubmit={form.submit->Formality.Dom.preventDefault}>
                    <div className="field-title">
                        <label>"Site Name:" -> React.string</label>
                        <input
                            type_="text"
                            value={scrap.site_name}
                            disabled={form.submitting}
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
                                placeholder={scrap.description}
                                disabled={form.submitting}
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
                            (form.submitting ? "Updating..." : "Update") -> React.string
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
                </CenterPosition>
            </Container> 
    }
}