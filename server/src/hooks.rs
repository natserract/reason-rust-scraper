
use rocket_contrib::json::{JsonValue};

#[catch(404)]
pub fn error_status() -> JsonValue {
    json!({
        "status": "Error",
        "reason": "Resource was not found {}",
    })
}
