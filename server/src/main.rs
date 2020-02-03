
#![feature(proc_macro_hygiene, decl_macro, plugin)]
#![allow(dead_code)]
#![allow(unused_imports)]

#[macro_use] extern crate rocket;
#[macro_use] extern crate rocket_contrib;
#[macro_use] extern crate diesel;
extern crate chrono;
extern crate reqwest;

mod routes;
mod pool;
mod hooks;
mod models;
mod database;
mod schema;

fn main() {
   pool::onfire().launch();
}
