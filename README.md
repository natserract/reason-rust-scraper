# Reason Rust Scraper
This is a code repository for implementing how to scraping and crawling websites using Rust, and ReasonML. This project was originally made by me with the aim of tools in my company to work. However, because of the sudden change of ideas and concepts finally i make it like this hehe, as well as my first project when learning & use ReasonML.

If you have never heard of scraping, try to read this [web scraping](https://en.wikipedia.org/wiki/Web_scraping) for more information.

<img src="https://github.com/alfinsuryaS/reason-rust-scraper/blob/master/screenshot.gif" alt="screenshot" width="100%"/>


## Requirements
  ### Server
   1. [Rust](https://www.rust-lang.org/tools/install)
   2. [Rustup](https://rustup.rs/)
   3. [Cargo](https://doc.rust-lang.org/cargo/getting-started/installation.html)
   4. [Apache & MySQL](https://www.apachefriends.org/index.html)
   
  ### Client
   1. [Node](https://nodejs.org/)
   2. [Bucklescript](https://bucklescript.github.io/)
  
  
## Getting started
   1. Clone this repo
   2. Start **Apache** & **MySQL** server
   3. Create new database and `.env` file and set config, like this [.env](https://github.com/alfinsuryaS/reason-rust-scraper/blob/master/.env.example)
   4. `npm install` to install all req'd dependencies
   
## Running
  To running this project locally:
 
  1. For MacOS, and you have a iTerm. You can running easily, type this command 
  
  ```bash 
   $ sudo chmod +x ./run.sh && ./run.sh
  ```
  2. Or, you can running manually, for client side: 

 ```bash
   $ npm start
  ``` 
  3. Open a new terminal tab/window, and type this command:

  ```bash
   $ npm server
  ```
  4. Open a new terminal tab/window again, for running server side:
  
  ```bash
   $ cargo run
  ```
  5. Open in you browser [http://localhost:8000/](http://localhost:8000/)
 
## Testing
```bash
$ sudo chmod +x ./test.sh && ./test.sh
```

## Build
#### Client:
```bash
$ npm run build
```

#### Server:
```bash
$ cargo build
```