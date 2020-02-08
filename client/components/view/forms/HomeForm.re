open Formality;

module Make = {
    type field = 
      | SiteName
      | Description;

    type state = {
        site_name: string,
        description: string,
    };

    type message = string;
    type submissionError = unit;

    let debounceInterval = Formality.Async.debounceInterval;

    module SiteNameField = {
        let update = (state, value) => {...state, site_name: value};

        let validator = {
            Async.{
                field: SiteName,
                strategy: OnSubmit,
                dependents: None,
                validate: ({ site_name }) => {
                    switch site_name {
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
                strategy: OnSubmit,
                dependents: None,
                validate: ({description}) => {
                    switch description {
                        | "" => Error("Description is required")
                        | _ => Ok(Valid)
                    };
                },
                validateAsync: None,
            }
        }
    };

    let validators = [
        SiteNameField.validator,
        DescField.validator,
    ]
};
