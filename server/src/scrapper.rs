use select::document::Document;

pub mod lib {
    #[tokio::main]
    pub async fn status(some_url: &str) -> Result<String, reqwest::Error> {
        let request = reqwest::get(some_url).await?;
        let request_status = request.status();
        Ok(String::from(&request_status.to_string()))
    }

    #[tokio::main]
    pub async fn remote_addr(some_url: &str) -> Result<String, reqwest::Error> {
        let request = reqwest::get(some_url).await?;
        let remote_addr = request.remote_addr();
        match remote_addr {
            Some(e) => Ok(e.to_string()),
            None => panic!("Error"),
        }
    }

    #[tokio::main]
    pub async fn html(some_url: &str) -> Result<String, reqwest::Error> {
        let request = reqwest::get(some_url).await?;
        let request_body = request.text_with_charset("utf-8").await?;
        Ok(String::from(request_body))
    }

    #[tokio::main]
    pub async fn css() -> Result<String, reqwest::Error>{
        // let mut result = String::new();
        // result.push_str("");
        // result.push_str("");

        let request = reqwest::get("https://www.robertriccilaw.com/design/css/site.css").await?;
        let status_req = request.status();
        let get_req_status = reqwest::StatusCode::from(status_req).is_success();

        let mut result = String::new();
        let request_css_body = request.text().await?;

        match get_req_status {
            true =>  result.push_str(&request_css_body),
            false => result.push_str("Sorry the path of css file is /design/css/")
        };

        Ok(result)
    }

    #[tokio::main]
    pub async fn grab_all_links(some_url: &str) -> Result<String, reqwest::Error> {
        let request = reqwest::get(some_url).await?;
        let request_body = request.text().await?;
        let fragment = scraper::Html::parse_document(&request_body);
        let selector = scraper::Selector::parse("a").unwrap();

        let mut result = String::new();

        {
            for node in fragment.select(&selector) {
                let get_response = node.value().attr("href").unwrap();
                result.push_str(
                    get_response
                )
            }
        }

        Ok(result)
    }
}
