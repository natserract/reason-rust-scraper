
use crate::pool;
use rocket_contrib::json::{Json, JsonValue};
use rocket::http::Status;

use crate::models;
use models::scrap_models::{
    Scraps,
    NewScraps
};

use crate::database;
use database::scrap_db as action;

#[get("/api/scraps")]
pub fn view_all_scraps(connection: pool::Connection) -> JsonValue {
    let result = action::query_view_scraps_data(&connection);
    json!({
        "result": result
    })
}

#[post("/api/scraps/post", data = "<scrap_data>")]
pub fn create_scrap_post(scrap_data: Json<NewScraps>, connection: pool::Connection) -> Json<Scraps> {
    let new_scrap_post = scrap_data.into_inner();
    let field_site_name = new_scrap_post.site_name;
    let field_description = new_scrap_post.description;

    Json(action::query_create_scrap_post(
        &connection,
        field_site_name,
        field_description,
    ))
}