use diesel;
use diesel::prelude::*;
use rocket_contrib::json::{Json, JsonError, JsonValue};

use crate::schema::scrap;
use crate::schema::scrap::dsl::scrap as all_issues;

use crate::models;
use models::scrap_models::{NewScraps, Scraps, UpdateScraps};

use crate::utils;
use chrono::Local;

use crate::scrapper;

type ScrapOpt = Option<String>;

pub fn query_view_scraps_data(connection: &MysqlConnection) -> Vec<Scraps> {
    scrap::table
        .order(scrap::id.desc())
        .load::<Scraps>(connection)
        .unwrap()
}

pub fn query_view_scraps_data_byid(id: i32, connection: &MysqlConnection) -> Option<Scraps> {
    scrap::table
        .find(id)
        .get_result(connection)
        .map_err(|err| println!("Error: {}", err))
        .ok()
}

pub fn query_create_scrap_post(
    connection: &MysqlConnection,
    site_name: &str,
    description: &str,
) -> Scraps {
    let created_at = Some(Local::now().naive_local());
    let scrap_body = scrapper::lib::html(site_name);
    let scrap_ip_address = scrapper::lib::remote_addr(site_name);
    let scrap_all_links = scrapper::lib::grab_all_links(site_name);
    let scrap_all_img = scrapper::lib::grab_all_images(site_name);
    let scrap_headers = scrapper::lib::headers(site_name);

    let new_scrap_post = &NewScraps {
        site_name,
        description,
        headers: &utils::result_res(scrap_headers),
        ip_address: &utils::result_res(scrap_ip_address),
        html_code: &utils::result_res(scrap_body),
        css_code: "CSS",
        all_links: &utils::result_res(scrap_all_links),
        images: &utils::result_res(scrap_all_img),
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

pub fn query_update_user(id: i32, connection: &MysqlConnection, scrap_data: UpdateScraps) -> bool {
    let updated_at = Some(Local::now().naive_local());
    let ip_address = scrapper::lib::remote_addr_opt(scrap_data.site_name.clone());
    let html_code = scrapper::lib::html_opt(scrap_data.site_name.clone());
    let all_links = scrapper::lib::grab_all_links_opt(scrap_data.site_name.clone());
    let all_img = scrapper::lib::grab_all_images_opt(scrap_data.site_name.clone());
    let headers = scrapper::lib::headers_opt(scrap_data.site_name.clone());
    let scrap_ip_address: ScrapOpt = ip_address.ok();
    let scrap_html_code: ScrapOpt = html_code.ok();
    let scrap_all_links: ScrapOpt = all_links.ok();
    let scrap_all_img: ScrapOpt = all_img.ok();
    let scrap_headers: ScrapOpt = headers.ok();

    let data = &UpdateScraps {
        created_at: None,
        updated_at: updated_at,
        headers: scrap_headers,
        ip_address: scrap_ip_address,
        html_code: scrap_html_code,
        all_links: scrap_all_links,
        images: scrap_all_img,
        ..scrap_data.clone()
    };
    diesel::update(scrap::table.find(id))
        .set(data)
        .execute(connection)
        .is_ok()
}
