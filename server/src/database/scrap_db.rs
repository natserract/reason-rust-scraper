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

use crate::scrapper;

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
    let get_body_response = scrapper::lib::html(site_name);
    let get_ip_address = scrapper::lib::remote_addr(site_name);
    let get_all_links = scrapper::lib::grab_all_links(site_name);
    let get_css_response = scrapper::lib::css();

    let new_scrap_post = &NewScraps {
        site_name,
        description,
        headers: "headers",
        ip_address: &hooks::result_res(get_ip_address),
        html_code: &hooks::result_res(get_body_response),
        css_code: &hooks::result_res(get_css_response),
        all_links: &hooks::result_res(get_all_links),
        images: "Images",
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