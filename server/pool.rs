
use diesel::mysql::MysqlConnection;
use diesel::r2d2::{ConnectionManager, Pool, PooledConnection};
use rocket_cors;

use rocket::http::{
    Status,
    Method
};
use rocket::request::{self, FromRequest};
use rocket::{Outcome, Request, State};
use rocket_cors::{
    AllowedHeaders,
    AllowedOrigins,
    Error,
    Cors,
    CorsOptions
};
use std::ops::Deref;

use super::routes;
use routes::{scrap_routes};

use dotenv::dotenv;
use std::env;

use crate::utils;
use crate::models;

use mime::Mime;

type MysqlPool = Pool<ConnectionManager<MysqlConnection>>;

fn init_pool(db_url: String) -> MysqlPool {
    let connect = ConnectionManager::<MysqlConnection>::new(db_url);
    Pool::new(connect).expect("Failed to create pool!")
}


fn enable_cors() -> Cors {
    // Cors::from_options(&Default::default()).expect("Cors can't be created")
    let allowed_origins = AllowedOrigins::some_exact(&["http://localhost:8000"]);
    
    CorsOptions {
        allowed_origins,
        allowed_methods: vec![
            Method::Get, 
            Method::Post,
            Method::Put,
            Method::Delete,
            Method::Head,
            Method::Options,
        ].into_iter().map(From::from).collect(),
        allowed_headers: AllowedHeaders::some(&[
            "Authorization",
            "Accept: image/*",
            "Accept: */*",
            "Access-Control-Allow-Origin: *",
            "Content-Type",
        ]),
        allow_credentials: true,
        ..Default::default()
    }
    .to_cors()
    .expect("Error when building cors")

}

pub fn server() -> rocket::Rocket {
    dotenv().ok();
    let database_url = env::var("DATABASE_URL").expect("DATABASE_URL must be set!");
    let pool = init_pool(database_url);

    

    rocket::ignite()
        .manage(pool)
        .mount(
            "/",
            routes![
                scrap_routes::view_all_scraps,
                scrap_routes::view_scrap,
                scrap_routes::create_scrap_post,
                scrap_routes::update_scrap_post,
            ],
        )
        .attach(enable_cors())
        .register(catchers![utils::error_status])
}

pub struct Connection(pub PooledConnection<ConnectionManager<MysqlConnection>>);

impl<'a, 'r> FromRequest<'a, 'r> for Connection {
    type Error = ();

    fn from_request(request: &'a Request<'r>) -> request::Outcome<Self, Self::Error> {
        let pool = request.guard::<State<MysqlPool>>()?;
        match pool.get() {
            Ok(conn) => Outcome::Success(Connection(conn)),
            Err(_) => Outcome::Failure((Status::ServiceUnavailable, ())),
        }
    }
}

impl Deref for Connection {
    type Target = MysqlConnection;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}
