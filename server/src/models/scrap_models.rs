use crate::schema::scrap;
use chrono::NaiveDateTime;

use rocket_contrib::json::{Json, JsonValue};
use serde::{Deserialize, Serialize};

#[derive(Serialize, Queryable)]
pub struct Scraps {
    pub id: i32,
    pub site_name: String,
    pub headers: String,
    pub body: String,
    pub created_at: Option<NaiveDateTime>,
    pub updated_at: Option<NaiveDateTime>,
}

