
#[cfg(test)]
mod tests {
    use crate::pool;
    use rocket::local::Client;
    use rocket::http::Status;

    #[test]
    fn test_view_all_scraps() {
        let client = Client::new(pool::server()).expect("valid");
        let response = client.get("/api/scraps").dispatch();

        assert_eq!(response.status(), Status::Ok);
    }
}