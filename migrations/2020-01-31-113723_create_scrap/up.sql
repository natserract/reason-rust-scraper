-- Your SQL goes here

CREATE TABLE scrap (
  id INTEGER AUTO_INCREMENT PRIMARY KEY NOT NULL,
  name varchar(191) NOT NULL,
  email varchar(191) UNIQUE NOT NULL,
  password varchar(191) NOT NULL,
  created_at TIMESTAMP NULL,
  updated_at TIMESTAMP NULL
);
