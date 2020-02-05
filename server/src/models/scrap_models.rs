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
    pub ip_address: String,
    pub html_code: String,
    pub css_code: String,
    pub all_links: String,
    pub images: String,
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
    pub ip_address: &'a str,
    #[serde(skip_deserializing)]
    pub html_code: &'a str,
    #[serde(skip_deserializing)]
    pub css_code: &'a str,
    #[serde(skip_deserializing)]
    pub all_links: &'a str,
    #[serde(skip_deserializing)]
    pub images: &'a str,
    #[serde(skip_deserializing)]

    pub created_at: Option<NaiveDateTime>,
    #[serde(skip_deserializing)]
    pub updated_at: Option<NaiveDateTime>,
}

#[table_name = "scrap"]
#[derive(Serialize, Deserialize, AsChangeset, Debug, Clone)]
pub struct UpdateScraps {
   pub site_name: Option<String>,
   pub description: Option<String>,

   pub ip_address: Option<String>,

   #[serde(skip_deserializing)]
   pub created_at: Option<NaiveDateTime>,
   pub updated_at: Option<NaiveDateTime>,
}
