-- MySQL dump 10.13  Distrib 8.0.23, for Win64 (x86_64)
--
-- Host: localhost    Database: bd_punto_venta
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `clientes`
--

DROP TABLE IF EXISTS `clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clientes` (
  `idcliente` int NOT NULL AUTO_INCREMENT,
  `nombres` varchar(60) DEFAULT NULL,
  `apellidos` varchar(60) DEFAULT NULL,
  `nit` varchar(12) DEFAULT NULL,
  `genero` bit(1) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  `correo_electronico` varchar(45) DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idcliente`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clientes`
--

LOCK TABLES `clientes` WRITE;
/*!40000 ALTER TABLE `clientes` DISABLE KEYS */;
INSERT INTO `clientes` VALUES (1,'Luis','Martinez','3388272',_binary '\0','33778899','luiismarti@gmail.com','2015-09-18 00:00:00'),(2,'Mariana','Castellana','81376',_binary '','44226178','Marianita66@gmail.com','2016-02-29 00:00:00'),(3,'Emily','Valencia','81376',_binary '','55669988','valenciaemy66@live.com','2017-11-06 00:00:00'),(4,'Jorge Sebastian','Aldana','4838372',_binary '\0','42561188','gorgeja@hotmail.com','2020-04-02 00:00:00'),(5,'Katerhine','Gonzalez','29128174',_binary '','22890712','Kathygonzalez@hotmail.com','2021-01-04 00:00:00'),(6,'Rolando Alfredo','Masilla Garcia','23553',_binary '','245436','mansilla@gmail.com','1980-12-03 11:20:09');
/*!40000 ALTER TABLE `clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras`
--

DROP TABLE IF EXISTS `compras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras` (
  `idcompras` int NOT NULL AUTO_INCREMENT,
  `no_orden_compra` int DEFAULT NULL,
  `idproveedor` int DEFAULT NULL,
  `fecha_orden` date DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idcompras`),
  KEY `idproveedores_proveedores_compras_idx` (`idproveedor`),
  CONSTRAINT `idproveedores_proveedores_compras` FOREIGN KEY (`idproveedor`) REFERENCES `proveedores` (`idproveedores`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras`
--

LOCK TABLES `compras` WRITE;
/*!40000 ALTER TABLE `compras` DISABLE KEYS */;
INSERT INTO `compras` VALUES (1,10001,1,'2021-03-15','2021-04-01 00:00:00'),(2,20022,2,'2021-03-03','2021-03-30 00:00:00'),(3,30013,2,'2021-03-15','2021-03-30 00:00:00'),(4,40045,4,'2021-03-14','2021-04-02 00:00:00'),(5,50001,3,'2021-03-16','2021-04-03 00:00:00');
/*!40000 ALTER TABLE `compras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `compras_detalle`
--

DROP TABLE IF EXISTS `compras_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `compras_detalle` (
  `idcompras_detalle` bigint NOT NULL AUTO_INCREMENT,
  `idcompra` int DEFAULT NULL,
  `idproducto` int DEFAULT NULL,
  `cantidad` int DEFAULT NULL,
  `precio_costo_unitario` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`idcompras_detalle`),
  KEY `idcompra_compras_compras_detalle_idx` (`idcompra`),
  KEY `idproducto_productos_compras_detalle_idx` (`idproducto`),
  CONSTRAINT `idcompra_compras_compras_detalle` FOREIGN KEY (`idcompra`) REFERENCES `compras` (`idcompras`) ON UPDATE CASCADE,
  CONSTRAINT `idproducto_productos_compras_detalle` FOREIGN KEY (`idproducto`) REFERENCES `productos` (`idproductos`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `compras_detalle`
--

LOCK TABLES `compras_detalle` WRITE;
/*!40000 ALTER TABLE `compras_detalle` DISABLE KEYS */;
INSERT INTO `compras_detalle` VALUES (2,NULL,NULL,75,14.00),(3,NULL,NULL,40,10.00),(4,NULL,NULL,40,10.00),(5,NULL,NULL,40,10.00),(6,NULL,NULL,20,12.00);
/*!40000 ALTER TABLE `compras_detalle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `empleados`
--

DROP TABLE IF EXISTS `empleados`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `empleados` (
  `idEmpleados` int NOT NULL AUTO_INCREMENT,
  `nombres` varchar(60) DEFAULT NULL,
  `apellidos` varchar(60) DEFAULT NULL,
  `direccion` varchar(80) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  `DPI` varchar(15) DEFAULT NULL,
  `genero` bit(1) DEFAULT NULL,
  `fecha_nacimiento` date DEFAULT NULL,
  `idpuesto` smallint DEFAULT NULL,
  `fecha_inicio_labores` date DEFAULT NULL,
  `fechaingreso` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idEmpleados`),
  KEY `idpuesto_puestos_empleados_idx` (`idpuesto`),
  CONSTRAINT `idpuesto_puestos_empleados` FOREIGN KEY (`idpuesto`) REFERENCES `puestos` (`idpuestos`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empleados`
--

LOCK TABLES `empleados` WRITE;
/*!40000 ALTER TABLE `empleados` DISABLE KEYS */;
INSERT INTO `empleados` VALUES (1,'Carlos','Rivera','3 calle 2-08, Ciudad Vieja Sac','4487887','3818382370103',_binary '\0','1998-11-04',NULL,'2014-03-10','2014-01-08'),(2,'Kennet','Galindo','4 calle poniente 4-01, Antigua G.','33000103','2414913480201',_binary '\0','1994-04-10',NULL,'2010-06-08','2014-08-08'),(3,'Luisa','Hernandez','Calzada Santa Lucia 3A, Antigua G.','24677642','2176139870101',_binary '','1999-12-25',NULL,'2021-02-03','2020-12-19'),(4,'Mario','Lopez','Km 29.8 casa 24 San Lucas Sac.','11224488','3747123160603',_binary '\0','1998-08-02',NULL,'2018-10-12','2018-08-18'),(5,'Andrea','Castillo','2 avenida casa 12 Jocotenango','32485231','424234772720101',_binary '','1992-03-19',NULL,'2021-03-03','2021-01-18'),(7,'Daniel Noe','Lopez Castillo','Antigua G','55566778','24534654780',_binary '','1999-01-01',1,'2020-01-01','2019/09/05 13:00:00'),(8,'Maria del Rosario','Lopez Ramirez','Guatemala','3333333','6576586794',_binary '\0','1999-01-01',3,'2021-02-01','2020-12-01');
/*!40000 ALTER TABLE `empleados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `marcas`
--

DROP TABLE IF EXISTS `marcas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `marcas` (
  `idmarcas` smallint NOT NULL AUTO_INCREMENT,
  `marca` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idmarcas`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `marcas`
--

LOCK TABLES `marcas` WRITE;
/*!40000 ALTER TABLE `marcas` DISABLE KEYS */;
INSERT INTO `marcas` VALUES (1,'Azucar Cañareal'),(2,'Ducal'),(3,'Jugos del Frutal'),(4,'Diana'),(5,'Kellogg\'s'),(6,'La Nacional');
/*!40000 ALTER TABLE `marcas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `productos`
--

DROP TABLE IF EXISTS `productos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `productos` (
  `idproductos` int NOT NULL AUTO_INCREMENT,
  `producto` varchar(50) DEFAULT NULL,
  `idmarca` smallint DEFAULT NULL,
  `descripcion` varchar(100) DEFAULT NULL,
  `imagen` varchar(30) DEFAULT NULL,
  `precio_costo` decimal(8,2) DEFAULT NULL,
  `precio_venta` decimal(8,2) DEFAULT NULL,
  `existencia` int DEFAULT NULL,
  `fecha_ingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idproductos`),
  KEY `idmarca_marcas_productos_idx` (`idmarca`),
  CONSTRAINT `idmarca_marcas_productos` FOREIGN KEY (`idmarca`) REFERENCES `marcas` (`idmarcas`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `productos`
--

LOCK TABLES `productos` WRITE;
/*!40000 ALTER TABLE `productos` DISABLE KEYS */;
INSERT INTO `productos` VALUES (1,'Azucar Caña Real',NULL,'Bolsa de azucar caña real 5 lb','---',14.00,18.00,125,'2021-04-01 00:00:00'),(2,'Frijoles Ducal',NULL,'Bote de frijoles volteados ducal 16oz','---',10.00,15.00,80,'2021-03-30 00:00:00'),(3,'Jugo pack',NULL,'Paquete de 6 jugos del frutal','---',12.00,16.00,33,'2021-02-09 00:00:00'),(4,'Cereal Chococrispis',NULL,'Caja de cereal Kellogs 530g','---',24.00,32.00,72,'2021-04-02 00:00:00'),(5,'Leche Anchor',NULL,'Bolsa de leche Anchor 410g','---',120.00,144.00,44,'2021-04-03 00:00:00');
/*!40000 ALTER TABLE `productos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proveedores`
--

DROP TABLE IF EXISTS `proveedores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proveedores` (
  `idproveedores` int NOT NULL AUTO_INCREMENT,
  `proveedor` varchar(60) DEFAULT NULL,
  `NIT` varchar(12) DEFAULT NULL,
  `direccion` varchar(80) DEFAULT NULL,
  `telefono` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`idproveedores`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proveedores`
--

LOCK TABLES `proveedores` WRITE;
/*!40000 ALTER TABLE `proveedores` DISABLE KEYS */;
INSERT INTO `proveedores` VALUES (1,'Azucar de Guatemala','2834266','Km 148 carretera al Pacifico Palin Escuintla lote12','77880099'),(2,'Cereales de Guatemala','138712','46 calle 24-50 zona 12 Guatemela','78047887'),(3,'Cerveceria Centroamericana','1000024','Km 30.7 6calle Finca el Zapote Ciudad de Guatemala','74877814'),(4,'Alimentos de Centro America','42942787','Avenida Petapa 12 avenida 13-60 zona 12 G.','79886742'),(5,'La Nacional','3389282','Km 16.5 Carretera Roosvelt 4-81 zona 1 de Mixco Guatemala','72449270'),(6,'Licores de Guatemala SA','25673','Km 128 Calzada Roosvelt Mixco, Guatemala','54759885');
/*!40000 ALTER TABLE `proveedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `puestos`
--

DROP TABLE IF EXISTS `puestos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `puestos` (
  `idpuestos` smallint NOT NULL AUTO_INCREMENT,
  `puesto` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idpuestos`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `puestos`
--

LOCK TABLES `puestos` WRITE;
/*!40000 ALTER TABLE `puestos` DISABLE KEYS */;
INSERT INTO `puestos` VALUES (1,'Gerente'),(2,'Subgerente'),(3,'Encargado de tienda'),(4,'Vendedor'),(6,'Cajero'),(7,'Conserje'),(9,'Cajero');
/*!40000 ALTER TABLE `puestos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas`
--

DROP TABLE IF EXISTS `ventas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas` (
  `idventas` int NOT NULL AUTO_INCREMENT,
  `nofactura` int DEFAULT NULL,
  `serie` char(1) DEFAULT NULL,
  `fechafactura` date DEFAULT NULL,
  `idcliente` int DEFAULT NULL,
  `idempleado` int DEFAULT NULL,
  `fechaingreso` datetime DEFAULT NULL,
  PRIMARY KEY (`idventas`),
  KEY `idcliente_clientes_ventas_idx` (`idcliente`),
  KEY `idempleado_empleados_ventas_idx` (`idempleado`),
  CONSTRAINT `idcliente_clientes_ventas` FOREIGN KEY (`idcliente`) REFERENCES `clientes` (`idcliente`) ON UPDATE CASCADE,
  CONSTRAINT `idempleado_empleados_ventas` FOREIGN KEY (`idempleado`) REFERENCES `empleados` (`idEmpleados`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas`
--

LOCK TABLES `ventas` WRITE;
/*!40000 ALTER TABLE `ventas` DISABLE KEYS */;
INSERT INTO `ventas` VALUES (1,100001,'1','2021-04-01',1,2,'2021-04-01 00:00:00'),(2,20022,'1','2021-04-02',2,1,'2021-04-02 00:00:00'),(3,30013,'2','2021-04-03',1,4,'2021-04-03 00:00:00'),(4,40045,'2','2021-04-04',4,3,'2021-04-04 00:00:00'),(5,50001,'2','2021-04-04',2,4,'2021-04-04 00:00:00');
/*!40000 ALTER TABLE `ventas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ventas_detalle`
--

DROP TABLE IF EXISTS `ventas_detalle`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ventas_detalle` (
  `idventas_detalle` bigint NOT NULL,
  `idventa` int DEFAULT NULL,
  `idproducto` int DEFAULT NULL,
  `cantidad` varchar(45) DEFAULT NULL,
  `precio_unitario` decimal(8,2) DEFAULT NULL,
  PRIMARY KEY (`idventas_detalle`),
  KEY `idventa_ventas_ventas_detalle_idx` (`idventa`),
  KEY `idproducto_productos_ventas_detalle_idx` (`idproducto`),
  CONSTRAINT `idproducto_productos_ventas_detalle` FOREIGN KEY (`idproducto`) REFERENCES `productos` (`idproductos`) ON UPDATE CASCADE,
  CONSTRAINT `idventa_ventas_ventas_detalle` FOREIGN KEY (`idventa`) REFERENCES `ventas` (`idventas`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ventas_detalle`
--

LOCK TABLES `ventas_detalle` WRITE;
/*!40000 ALTER TABLE `ventas_detalle` DISABLE KEYS */;
INSERT INTO `ventas_detalle` VALUES (1,1,1,'4',18.00),(2,2,4,'2',12.00),(3,3,3,'1',32.00),(4,4,1,'2',18.00),(5,5,2,'3',15.00);
/*!40000 ALTER TABLE `ventas_detalle` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-23 19:03:30
