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
    pub async fn remote_addr_opt(some_url: Option<String>) -> Result<String, reqwest::Error> {
        let check_url = some_url.unwrap();
        let request = reqwest::get(&check_url).await?;
        let request_status = request.remote_addr();

        match request_status {
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
    pub async fn grab_all_links(some_url: &str) -> Result<String, reqwest::Error> {
        let request = reqwest::get(some_url).await?;
        let request_body = request.text().await?;
        let fragment = scraper::Html::parse_document(&request_body);
        let selector = scraper::Selector::parse("a").unwrap();

        let mut result = String::new();

        {
            for node in fragment.select(&selector) {
                let get_response = node.value().attr("href").unwrap();
                result.push_str(get_response);
                result.push_str("\t ");
            }
        }

        Ok(result)
    }

    #[tokio::main]
    pub async fn grab_all_images(some_url: &str) -> Result<String, reqwest::Error> {
        let request = reqwest::get(some_url).await?;
        let request_body = request.text().await?;
        let fragment = scraper::Html::parse_document(&request_body);
        let selector = scraper::Selector::parse("img").unwrap();

        let mut result = String::new();

        {
            for node in fragment.select(&selector) {
                let get_response = node.value().attr("src").unwrap();
                result.push_str(get_response);
                result.push_str("\t ");
            }
        }

        Ok(result)
    }
}
