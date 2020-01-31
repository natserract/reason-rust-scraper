use diesel;
use diesel::mysql::MysqlConnection;
use diesel::prelude::*;

use crate::schema::scrap;
use crate::schema::scrap::dsl::scrap as all_issues;

use diesel::result::{DatabaseErrorKind, Error};

use crate::models;
use models::scrap_models::Scraps;

use crate::hooks;
use chrono::Local;

pub fn query_view_all_scraps(connection: &MysqlConnection) -> Vec<Scraps> {
    scrap::table
        .order(scrap::id.desc())
        .load::<Scraps>(connection)
        .unwrap()
}
