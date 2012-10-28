SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `RouteDB` ;
CREATE SCHEMA IF NOT EXISTS `RouteDB` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;

-- -----------------------------------------------------
-- Table `RouteDB`.`IP_Addresses`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RouteDB`.`IP_Addresses` ;

CREATE  TABLE IF NOT EXISTS `RouteDB`.`IP_Addresses` (
  `idIP_Address` VARCHAR(16) NOT NULL ,
  `Domain` VARCHAR(75) NULL ,
  PRIMARY KEY (`idIP_Address`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RouteDB`.`Routes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RouteDB`.`Routes` ;

CREATE  TABLE IF NOT EXISTS `RouteDB`.`Routes` (
  `idRoute` INT NOT NULL ,
  `Date` DATE NOT NULL ,
  `RouteFrom` VARCHAR(16) NOT NULL ,
  `RouteTo` VARCHAR(16) NOT NULL ,
  PRIMARY KEY (`idRoute`) ,
  INDEX `RouteFrom` (`RouteFrom` ASC) ,
  INDEX `RouteTo` (`RouteTo` ASC) ,
  CONSTRAINT `RouteFrom`
    FOREIGN KEY (`RouteFrom` )
    REFERENCES `RouteDB`.`IP_Addresses` (`idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `RouteTo`
    FOREIGN KEY (`RouteTo` )
    REFERENCES `RouteDB`.`IP_Addresses` (`idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `RouteDB`.`Hops`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RouteDB`.`Hops` ;

CREATE  TABLE IF NOT EXISTS `RouteDB`.`Hops` (
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
  INDEX `FirstIP` (`FirstIP` ASC) ,
  INDEX `SecondIP` (`SecondIP` ASC) ,
  INDEX `ThirdIP` (`ThirdIP` ASC) ,
  CONSTRAINT `idRoute`
    FOREIGN KEY (`RouteID` )
    REFERENCES `RouteDB`.`Routes` (`idRoute` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `FirstIP`
    FOREIGN KEY (`FirstIP` )
    REFERENCES `RouteDB`.`IP_Addresses` (`idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `SecondIP`
    FOREIGN KEY (`SecondIP` )
    REFERENCES `RouteDB`.`IP_Addresses` (`idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `ThirdIP`
    FOREIGN KEY (`ThirdIP` )
    REFERENCES `RouteDB`.`IP_Addresses` (`idIP_Address` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
