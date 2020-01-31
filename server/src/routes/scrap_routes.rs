
use crate::pool;
use rocket_contrib::json::{Json, JsonValue};
use rocket::http::Status;

use crate::models;
use crate::database;
use database::scrap_db as action;

#[get("/scraps")]
pub fn view_all_scraps(connection: pool::Connection) -> JsonValue {
    let result = action::query_view_all_scraps(&connection);
    json!({
        "data": result
    })
}