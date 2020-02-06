

use diesel;
use diesel::mysql::MysqlConnection;
use diesel::prelude::*;
use rocket_contrib::json::{Json, JsonValue, JsonError};

use crate::schema::scrap;
use crate::schema::scrap::dsl::scrap as all_issues;

use diesel::result::{DatabaseErrorKind, Error};

use crate::models;
use models::scrap_models::{
    Scraps,
    NewScraps,
    UpdateScraps
};

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


pub fn query_create_scrap_post(
    connection: &MysqlConnection,
    site_name: &str,
    description: &str,
) -> Scraps {
    
    let created_at = Some(Local::now().naive_local());
    let get_body_response = scrapper::lib::html(site_name);
    let get_ip_address = scrapper::lib::remote_addr(site_name);
    let get_all_links = scrapper::lib::grab_all_links(site_name);
    let get_all_img = scrapper::lib::grab_all_images(site_name);
    let get_headers = scrapper::lib::headers(site_name);

    let new_scrap_post = &NewScraps {
        site_name,
        description,
        headers: &utils::result_res(get_headers),
        ip_address: &utils::result_res(get_ip_address),
        html_code: &utils::result_res(get_body_response),
        css_code: "CSS",
        all_links: &utils::result_res(get_all_links),
        images: &utils::result_res(get_all_img),
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


pub fn query_update_user(
    id: i32,
    connection: &MysqlConnection,
    scrap_data: Json<UpdateScraps>
) -> bool {
    
    let updated_at = Some(Local::now().naive_local());

    //site_name moving here
    let ip_address = scrapper::lib::remote_addr_opt(scrap_data.site_name.clone());
    let html_code = scrapper::lib::html_opt(scrap_data.site_name.clone());
    let all_links = scrapper::lib::grab_all_links_opt(scrap_data.site_name.clone());
    let all_img = scrapper::lib::grab_all_images_opt(scrap_data.site_name.clone());
    
    let scrap_ip_address: ScrapOpt = ip_address.ok();
    let scrap_html_code: ScrapOpt = html_code.ok();
    let scrap_all_links: ScrapOpt = all_links.ok();
    let scrap_all_img: ScrapOpt = all_img.ok();

    let data = &UpdateScraps {
        created_at: None,
        updated_at: updated_at,
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