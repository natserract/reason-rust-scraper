

open Utils;
open HomeStyles;

type state = {
    result: Models.t,
};

type formState = 
    | Initial 
    | Loading
    | Submit

type formAction = 
  | NotSubmitted
  | LoadSubmit
  | Submitted;

[@react.component]
let make = (~id: string) => {
    let (state, dispatch) = React.useReducer(
        (_state, action) => {
            switch action {
                | NotSubmitted => Initial
                | LoadSubmit => Loading
                | Submitted => Submit
            };
        },
        Initial
    );

    let (value, setValue) = React.useState(() => {
        result: {
            site_name: "",
            description: "",
        }
    });

    React.useEffect0(() => {
        Js.Promise.(
            Models.API.fetchUpdate(id)
            |> then_(result => setValue(_ => { result: result}) |> resolve)
            |> catch(_err => Js.log("Error") |> resolve)
            |> ignore
        )
        None;
    });
    

    let handleChange = (e) => {
        e -> ReactEvent.Form.persist;
        if(e -> ReactEvent.Form.target##name === "site_name") {
            setValue(_ => {
                result: {
                    site_name: e -> ReactEvent.Form.target##value,
                    description: value.result.description
                }
            })
        } else if(e -> ReactEvent.Form.target##name === "description") {
            setValue(_ => {
                result: {
                    site_name: value.result.site_name,
                    description: e -> ReactEvent.Form.target##value
                }
            })
        }
    };
    

    let handleSubmit = (e) => {
        e -> ReactEvent.Form.preventDefault;
        dispatch(LoadSubmit);
        Js.Promise.(
            Models.API.update(id, value.result)
            |> then_(_ => dispatch(Submitted) |> resolve)
            |> catch(err => Js.log(err) |> resolve)
            |> ignore
        );
    };

    
    <Container>
        <CenterPosition>
        <h2 className=Styles.heading>(str("Update Data"))</h2>

        <form className=Styles.form onSubmit=(e => handleSubmit(e))>
            <div className="field-title">
                <label>"Site Name:" -> React.string</label>
                <input required=true type_="text" name="site_name" value=value.result.site_name onChange=(e => handleChange(e))/>
            </div>

            <div className="field-description">
                <label>"Detailed Description:" -> React.string</label>
                <textarea required=true name="description" value=value.result.description onChange=(e => handleChange(e))></textarea>
            </div>
            
            <button className=Styles.button type_="submit">
                {
                    switch state {
                        | Initial => "Update" -> str
                        | Loading => "Updating..." -> str
                        | Submit => "Updated" -> str
                    };
                }
            </button>
        </form>

        </CenterPosition>
    </Container> 
    
}