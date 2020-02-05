

use diesel;
use diesel::mysql::MysqlConnection;
use diesel::prelude::*;

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

    let new_scrap_post = &NewScraps {
        site_name,
        description,
        headers: "headers",
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
    scrap_data: UpdateScraps
) -> bool {
    
    let updated_at = Some(Local::now().naive_local());

    //Should be cloned!
    let site_name = scrap_data.site_name.clone();
    
    let ip_address = scrapper::lib::remote_addr_opt(site_name);
    let get_ip_address_res: Option<String> = ip_address.ok();

    let data = &UpdateScraps {
        created_at: None,
        updated_at: updated_at,
        ip_address: get_ip_address_res,
        ..scrap_data.clone() 
    };

    diesel::update(scrap::table.find(id))
        .set(data)
        .execute(connection)
        .is_ok()
}