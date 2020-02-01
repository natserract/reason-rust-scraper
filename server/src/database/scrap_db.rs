use diesel;
use diesel::mysql::MysqlConnection;
use diesel::prelude::*;

use crate::schema::scrap;
use crate::schema::scrap::dsl::scrap as all_issues;

use diesel::result::{DatabaseErrorKind, Error};

use crate::models;
use models::scrap_models::{
    Scraps,
    NewScraps
};

use crate::hooks;
use chrono::Local;

pub fn query_view_scraps_data(connection: &MysqlConnection) -> Vec<Scraps> {
    scrap::table
        .order(scrap::id.desc())
        .load::<Scraps>(connection)
        .unwrap()
}


pub fn query_create_scrap_post(
    connection: &MysqlConnection,
    site_name: &str,
    description: &str,
) -> Scraps {
    let created_at = Some(Local::now().naive_local());
    let new_scrap_post = &NewScraps {
        site_name,
        description,
        body: "Body",
        headers: "Headers",
        created_at: created_at,
        updated_at: None,
    };

    diesel::insert_into(scrap::table)
            .values(new_scrap_post)
            .execute(connection)
            .ok();

    scrap::table
        .order(scrap::id.desc())
        .first(connection)
        .unwrap()
}