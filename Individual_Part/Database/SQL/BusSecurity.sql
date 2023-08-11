-- phpMyAdmin SQL Dump
-- version 5.1.3
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 24, 2022 at 05:09 PM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 7.4.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `BusSecurity`
--

-- --------------------------------------------------------

--
-- Table structure for table `RFID`
--

CREATE TABLE `RFID` (
  `RFID` varchar(12) NOT NULL COMMENT 'pk',
  `StdID` int(4) NOT NULL COMMENT 'fk'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `RFID`
--

INSERT INTO `RFID` (`RFID`, `StdID`) VALUES
('13006F6B5391', 1),
('13006FA337F5', 2);

-- --------------------------------------------------------

--
-- Table structure for table `Student`
--

CREATE TABLE `Student` (
  `StdID` int(4) NOT NULL COMMENT 'PrimaryKey',
  `Name` varchar(25) NOT NULL,
  `Mobile_Number` int(12) NOT NULL,
  `Address` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `Student`
--

INSERT INTO `Student` (`StdID`, `Name`, `Mobile_Number`, `Address`) VALUES
(1, 'Taylor', 718564737, 'NO.09,1st cross lane,1st cross street, Mannar, North province'),
(2, 'Henryy', 718564735, 'No.12, cross lane, Mannar.');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `RFID`
--
ALTER TABLE `RFID`
  ADD PRIMARY KEY (`RFID`),
  ADD KEY `StdID` (`StdID`);

--
-- Indexes for table `Student`
--
ALTER TABLE `Student`
  ADD PRIMARY KEY (`StdID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Student`
--
ALTER TABLE `Student`
  MODIFY `StdID` int(4) NOT NULL AUTO_INCREMENT COMMENT 'PrimaryKey', AUTO_INCREMENT=36;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `RFID`
--
ALTER TABLE `RFID`
  ADD CONSTRAINT `rfid_ibfk_1` FOREIGN KEY (`StdID`) REFERENCES `Student` (`StdID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
