use crate::schema::scrap;
use chrono::NaiveDateTime;

use rocket_contrib::json::{Json, JsonValue};
use serde::{Deserialize, Serialize};

#[derive(Serialize, Queryable)]
pub struct Scraps {
    pub id: i32,
    pub site_name: String,
    pub description: String,
    pub headers: String,
    pub body: String,
    pub created_at: Option<NaiveDateTime>,
    pub updated_at: Option<NaiveDateTime>,
}

#[table_name = "scrap"]
#[derive(Serialize, Deserialize, Insertable, Queryable)]
pub struct NewScraps<'a> {
    pub site_name: &'a str,
    pub description: &'a str,
    
    #[serde(skip_deserializing)]
    pub headers: &'a str,
    
    #[serde(skip_deserializing)]
    pub body: &'a str,

    #[serde(skip_deserializing)]
    pub created_at: Option<NaiveDateTime>,
    #[serde(skip_deserializing)]
    pub updated_at: Option<NaiveDateTime>,
}
