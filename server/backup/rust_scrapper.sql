-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Waktu pembuatan: 01 Feb 2020 pada 01.27
-- Versi server: 10.4.10-MariaDB
-- Versi PHP: 7.1.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `rust_scrapper`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `scrap`
--

CREATE TABLE `scrap` (
  `id` int(11) NOT NULL,
  `site_name` varchar(50) NOT NULL,
  `description` varchar(100) NOT NULL,
  `headers` text NOT NULL,
  `body` text NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `__diesel_schema_migrations`
--

CREATE TABLE `__diesel_schema_migrations` (
  `version` varchar(50) NOT NULL,
  `run_on` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data untuk tabel `__diesel_schema_migrations`
--

INSERT INTO `__diesel_schema_migrations` (`version`, `run_on`) VALUES
('20200131113723', '2020-01-31 23:07:41');

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `scrap`
--
ALTER TABLE `scrap`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `__diesel_schema_migrations`
--
ALTER TABLE `__diesel_schema_migrations`
  ADD PRIMARY KEY (`version`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `scrap`
--
ALTER TABLE `scrap`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
