
open Utils;

module Form = HomeForm.Make;
module FormHook = Formality.Async.Make(Form);

let initialState = 
    Form.{ site_name: "", description: ""};

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
    
    <form onSubmit={form.submit->Formality.Dom.preventDefault}>
        <div className="field-title">
            <label>"Site Name (https/http):" -> React.string</label>
            <input
                type_="text"
                value={form.state.site_name}
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
                | Some(Error(message)) => React.string(message)
                | Some(Ok(Valid)) => 
                    <div>
                        {j|✓ Cakep|j}->React.string
                    </div>
                | Some(Ok(NoValue)) | None => React.null
            }}
        </div>

         <div className="field-description">
            <label>"Description" -> React.string</label>
                <input
                    type_="text"
                    value={form.state.description}
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
                    }
                />
                { switch (Description->(form.result)) {
                    | Some(Error(message)) => React.string("Failure")
                    | Some(Ok(Valid)) => 
                        <div>
                            {j|✓|j}->React.string
                        </div>
                    | Some(Ok(NoValue)) | None => React.null
                }}
         </div>
         <button disabled={form.submitting}>
                (form.submitting ? "Submitting..." : "Submit") -> React.string
         </button>
         {switch (form.status) {
            | Submitted =>
              <div>
                {j|✓ Berhasil|j}->React.string
              </div>
            | _ => React.null
            }}
    </form>

}