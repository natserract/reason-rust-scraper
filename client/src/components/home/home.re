open Formality;
open Utils;

type r = {
    site_name: string,
    description: string,
};

module Encode = {
    let client = (clientObj) => {
        Json.Encode.(
            object_([
                ("site_name", string(clientObj.site_name)),
                ("description", string(clientObj.description))
            ])
        )
    }
};

module Form = {
    type field = 
      | Title
      | Description;

    type state = {
        title: string,
        description: string,
    };

    type message = string;
    type submissionError = unit;

    let debounceInterval = Formality.Async.debounceInterval;

    module TitleField = {
        let update = (state, value) => {...state, title: value};

        let validator = {
            Async.{
                field: Title,
                strategy: OnFirstSuccessOrFirstBlur,
                dependents: None,
                validate: ({title}) => {
                    switch title {
                        | "" => Error("Title is required")
                        | _ => Ok(Valid)
                    };
                },
                validateAsync: None,
            }
        }
    };

    module DescField = {
        let update = (state, value) => {...state, description: value};

        let validator = {
            Async.{
                field: Description,
                strategy: OnFirstSuccessOrFirstBlur,
                dependents: None,
                validate: ({description}) => {
                    switch description {
                        | "" => Error("Title is required")
                        | _ => Ok(Valid)
                    };
                },
                validateAsync: None,
            }
        }
    };

    let validators = [
        TitleField.validator,
        DescField.validator,
    ]
};

module FormHook = Formality.Async.Make(Form);

let initialState = 
    Form.{title: "", description: ""};

[@react.component]
let make = () => {
    let form = 
        FormHook.useForm(
            ~initialState,
            ~onSubmit=(state, form) => {
                let payload = Js.Dict.empty();
                Js.Dict.set(payload, "site_name", Js.Json.string(state.title));
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
            <label>"Title" -> React.string</label>
            <input
                type_="text"
                value={form.state.title}
                disabled={form.submitting}
                onBlur={_ => form.blur(Title)}
                onChange={event => 
                    form.change(
                        Title,
                        Form.TitleField.update(
                            form.state,
                            event -> ReactEvent.Form.target##value,
                        )
                    )
                }
            />
            { switch (Title->(form.result)) {
                | Some(Error(message)) => React.string("Failure")
                | Some(Ok(Valid)) => 
                    <div>
                        {j|✓|j}->React.string
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
                {j|✓ Signed Up|j}->React.string
              </div>
            | _ => React.null
            }}
    </form>

}