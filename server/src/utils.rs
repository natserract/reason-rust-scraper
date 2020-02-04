
use rocket_contrib::json::{JsonValue};

#[catch(404)]
pub fn error_status() -> JsonValue {
    json!({
        "status": "Error",
        "reason": "Resource was not found {}",
    })
}

type ArgsType = Result<String, reqwest::Error>;
pub fn result_res(args: ArgsType) -> String {
    match args {
        Ok(result) => result,
        Err(err) => panic!("Error! Not Found: {}", err)
    }
}