
use crate::pool;
use rocket_contrib::json::{Json, JsonValue, JsonError};
use rocket::http::Status;

use crate::models;
use models::scrap_models::{
    Scraps,
    NewScraps,
    UpdateScraps
};

use crate::database;
use database::scrap_db as action;

#[get("/api/scraps")]
pub fn view_all_scraps(connection: pool::Connection) -> JsonValue {
    let result = action::query_view_scraps_data(&connection);
    json!({
        "results": result
    })
}

#[get("/api/scrap/<scrap_id>")]
pub fn view_scrap(scrap_id: i32, connection: pool::Connection) -> Option<JsonValue> {
    action::query_view_scraps_data_byid(scrap_id, &connection)
            .map(|data| json!({ 
                "results": data
            }))
}

#[post("/api/scraps/post", data = "<scrap_data>")]
pub fn create_scrap_post(scrap_data: Json<NewScraps>, connection: pool::Connection) -> Json<Scraps> {
    let new_scrap_post = scrap_data.into_inner();
    let field_site_name = new_scrap_post.site_name;
    let field_description = new_scrap_post.description;

    Json(
        action::query_create_scrap_post(
            &connection,
            field_site_name,
            field_description,
        )
    )
}


#[post("/api/scraps/update/<id>", data = "<scrap_data>")]
pub fn update_scrap_post(
    id: i32,
    scrap_data: Json<UpdateScraps>,
    connection: pool::Connection,
) -> String {
    let query = action::query_update_user(id, &connection, scrap_data.into_inner());
    match query {
        true => format!("Issue Post has been succesfully updated"),
        false => format!("Failed to update issue post"),
    }
}