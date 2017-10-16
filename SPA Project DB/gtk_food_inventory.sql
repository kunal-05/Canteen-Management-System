-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: localhost    Database: gtk
-- ------------------------------------------------------
-- Server version	5.7.17-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `food_inventory`
--

DROP TABLE IF EXISTS `food_inventory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `food_inventory` (
  `ID` int(3) unsigned NOT NULL AUTO_INCREMENT,
  `Type` varchar(30) NOT NULL,
  `Item` varchar(30) NOT NULL,
  `Price` int(3) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=64 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `food_inventory`
--

LOCK TABLES `food_inventory` WRITE;
/*!40000 ALTER TABLE `food_inventory` DISABLE KEYS */;
INSERT INTO `food_inventory` VALUES (1,'Fast Food','Veg Sandwich',25),(2,'Fast Food','Veg cheese Sandwich',35),(3,'Fast Food','Veg Grilled Sandwich',35),(4,'Fast Food','Veg Paneer Sandwich',35),(5,'Fast Food','Veg Cheese Grilled Sandwich',45),(6,'Fast Food','Cheese Chilli Toast',40),(7,'Fast Food','Paneer Roll',35),(8,'Fast Food','Veg Roll',30),(9,'Fast Food','Paneer Chilli Toast',40),(10,'Fast Food','Aloo Slice',30),(11,'Fast Food','Bread Butter',15),(12,'Fast Food','Pasta',50),(13,'Fast Food','Veg Pizza',50),(14,'Fast Food','Mendu Vada',20),(15,'Fast Food','Idli',20),(16,'Fast Food','Cutlet',20),(17,'Fast Food','Samosa Pav',15),(18,'Fast Food','Vada Pav',15),(19,'Beverages','Cavins Kesar Pista Badam',25),(20,'Beverages','Cavins Chocolate',25),(21,'Beverages','Cavins Vanilla',25),(22,'Beverages','Miranda',15),(23,'Beverages','Seven Up',15),(24,'Beverages','Coca Cola',15),(25,'Beverages','Pepsi',15),(26,'Confectionaries','Doughnut',50),(27,'Confectionaries','Slice Cake',20),(28,'Confectionaries','Swiss Roll',20),(29,'Confectionaries','Chocoalte Bomb',40),(30,'Confectionaries','Pastry',55),(31,'Confectionaries','Chocolate Mousse',50),(32,'Beverages','Coffee',15),(33,'Beverages','Tea',15),(34,'Packet Chips','Lays',15),(35,'Packet Chips','Balaji',15),(36,'Packet Chips','Kurkure',15),(37,'Beverages','Mountain Dew',15),(38,'Fast Food','Pav Bhaji',50),(39,'Fast Food','Butter Dosa',30),(40,'Fast Food','Cheese Dosa',35),(41,'Fast Food','Masala Dosa',45),(42,'Fast Food','Mysore Masala Dosa',45),(43,'Fast Food','Rava Sada Dosa',35),(44,'Fast Food','Palak Sada Dosa',40),(45,'Fast Food','Fried Rice',40),(46,'Fast Food','Veg Manchurian',40),(47,'Fast Food','Hakka Noodles',40),(48,'Fast Food','Schezwan Rice',50),(49,'Fast Food','Schezwan Noodles',50),(50,'Fast Food','Maggie',15),(51,'Chat','Panipuri',20),(52,'Chat','Sev puri',25),(53,'Chat','Bhel puri',25),(54,'Chat','Dahipuri',30),(55,'Chat','Ragadapattice',30),(56,'Chat','Cheese Sev puri',30),(57,'Jain food','Veg Pizza',45),(58,'Jain Food','Pasta',45),(59,'Jain Food','Veg Sandwich',25),(60,'Jain Food','Veg Grill Sandwich',30),(61,'Jain Food','Pav Bhaji',45),(62,'Jain Food','Hakka Noodles',40),(63,'Jain Food','Tawa Pulav',40);
/*!40000 ALTER TABLE `food_inventory` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-04-11 21:02:51
