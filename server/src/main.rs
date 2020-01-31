
#![allow(dead_code)]

#[tokio::main]
async fn main() -> Result<(), reqwest::Error> {
    println!("🔥 Enter your site want to scrap:");
    
    let mut input = String::new();

    match std::io::stdin().read_line(&mut input){
        Ok(_) => {
            println!("\nSite: {}", input);
            
            let len = input.len();
            input.truncate(len -1 );

            let uri = input + "/design/css/site.css";
            let response = reqwest::get(&uri).await?;

            println!("Status: {} \n", response.status());
            println!("Headers: {:?} \n", response.headers());

            let body = response.text().await?;
            println!("Body: \n{:#?}", body);
        }
        Err(err) => eprintln!("Error{}", err)
    }
    
    Ok(())
}
