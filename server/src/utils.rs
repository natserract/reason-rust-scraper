
use rocket_contrib::json::{JsonValue};

#[catch(404)]
pub fn error_status() -> JsonValue {
    json!({
        "status": "Error",
        "reason": "Resource was not found {}",
    })
}

pub type ArgsTypeRes = Result<String, reqwest::Error>;

pub fn result_res(args: ArgsTypeRes) -> String {
    match args {
        Ok(result) => result,
        Err(err) => panic!("Error! Not Found: {}", err)
    }
}

type ArgsTypeOption = Option<String>;
pub fn result_opt(args: ArgsTypeRes) -> ArgsTypeOption {
    match args {
       Ok(result) => Some(result),
       Err(_) => None
    }
}