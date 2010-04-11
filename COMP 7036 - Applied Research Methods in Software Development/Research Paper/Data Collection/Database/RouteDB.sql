SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `traceroute` ;
CREATE SCHEMA IF NOT EXISTS `traceroute` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;

-- -----------------------------------------------------
-- Table `traceroute`.`IP_Addresses`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `traceroute`.`IP_Addresses` ;

CREATE  TABLE IF NOT EXISTS `traceroute`.`IP_Addresses` (
  `idIP_Address` VARCHAR(16) NOT NULL ,
  `Domain` VARCHAR(75) NULL ,
  PRIMARY KEY (`idIP_Address`) ,
  UNIQUE INDEX `idIP_Address_UNIQUE` (`idIP_Address` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traceroute`.`Routes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `traceroute`.`Routes` ;

CREATE  TABLE IF NOT EXISTS `traceroute`.`Routes` (
  `idRoute` INT NOT NULL ,
  `Date` DATE NOT NULL ,
  `RouteFrom` VARCHAR(16) NOT NULL ,
  `RouteTo` VARCHAR(16) NOT NULL ,
  PRIMARY KEY (`idRoute`) ,
  INDEX `IP_Address` (`RouteFrom` ASC, `RouteTo` ASC) ,
  CONSTRAINT `IP_Address`
    FOREIGN KEY (`RouteFrom` , `RouteTo` )
    REFERENCES `traceroute`.`IP_Addresses` (`idIP_Address` , `idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traceroute`.`Hops`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `traceroute`.`Hops` ;

CREATE  TABLE IF NOT EXISTS `traceroute`.`Hops` (
  `idHop` INT UNSIGNED NOT NULL ,
  `RouteID` INT NOT NULL ,
  `HopNum` INT UNSIGNED NOT NULL ,
  `FirstIP` VARCHAR(16) NOT NULL ,
  `FirstDelay` DECIMAL(10) NULL ,
  `SecondIP` VARCHAR(16) NOT NULL ,
  `SecondDelay` DECIMAL(10) NULL ,
  `ThirdIP` VARCHAR(16) NOT NULL ,
  `ThurdDelay` DECIMAL(10) NULL ,
  PRIMARY KEY (`idHop`) ,
  UNIQUE INDEX `idHop` (`idHop` ASC) ,
  INDEX `idRoute` (`RouteID` ASC) ,
  INDEX `idIP_Address` (`FirstIP` ASC, `SecondIP` ASC, `ThirdIP` ASC) ,
  CONSTRAINT `idRoute`
    FOREIGN KEY (`RouteID` )
    REFERENCES `traceroute`.`Routes` (`idRoute` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `idIP_Address`
    FOREIGN KEY (`FirstIP` , `SecondIP` , `ThirdIP` )
    REFERENCES `traceroute`.`IP_Addresses` (`idIP_Address` , `idIP_Address` , `idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
