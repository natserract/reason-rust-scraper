-- Your SQL goes here

CREATE TABLE scrap (
  id INTEGER AUTO_INCREMENT PRIMARY KEY NOT NULL,
  site_name varchar(50) NOT NULL,
  description varchar(100) NOT NULL,
  headers TEXT NOT NULL,
  ip_address varchar(50) NOT NULL,
  html_code TEXT NOT NULL,
  all_links TEXT NOT NULL,
  images TEXT NOT NULL,
  created_at TIMESTAMP NULL,
  updated_at TIMESTAMP NULL
);
