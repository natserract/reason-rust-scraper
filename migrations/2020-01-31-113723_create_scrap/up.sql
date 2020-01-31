-- Your SQL goes here

CREATE TABLE scrap (
  id INTEGER AUTO_INCREMENT PRIMARY KEY NOT NULL,
  site_name varchar(50) NOT NULL,
  headers TEXT NOT NULL,
  body TEXT NOT NULL,
  created_at TIMESTAMP NULL,
  updated_at TIMESTAMP NULL
);
