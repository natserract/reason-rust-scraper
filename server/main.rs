
#![feature(proc_macro_hygiene, decl_macro, plugin)]
#![allow(dead_code)]
#![allow(unused_imports)]

#[macro_use] extern crate rocket;
#[macro_use] extern crate rocket_contrib;
#[macro_use] extern crate diesel;
extern crate chrono;
extern crate reqwest;
extern crate scraper;

mod routes;
mod pool;
mod utils;
mod models;
mod database;
mod schema;
mod scrapper;
mod tests;

fn main(){
    pool::server().launch();
}


