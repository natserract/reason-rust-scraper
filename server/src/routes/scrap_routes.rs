
use crate::pool;
use rocket_contrib::json::{Json, JsonValue};

use rocket::http::Status;

use crate::models;
use models::issues::{Issues, NewIssues, UpdateIssues};

use crate::database;
use database::issues as action;

#[get("/issues")]
pub fn view_all_issues(connection: config::Connection) -> JsonValue {
    let result = action::query_view_all_issues(&connection);
    json!({ "issues": result })
}