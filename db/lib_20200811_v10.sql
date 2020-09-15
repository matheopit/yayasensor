
-- -----------------------------------------------------

-- Table `mydb`.`wbd_version`
--INTERNAL FOR UPDATE
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS wbd_version (
  id INTEGER,
  desc TEXT,
  date TEXT,
  version INTEGER
);

CREATE TABLE IF NOT EXISTS wbd_sensor (
  idsensor INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT,
  desc TEXT
);

-- -----------------------------------------------------

-- Table `mydb`.`wbd_variety`
-- 
-- -----------------------------------------------------

CREATE TABLE IF NOT EXISTS wbd_weather (
  idweather INTEGER PRIMARY KEY AUTOINCREMENT,
  idsensor INTEGER,
  stamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
  temperature REAL DEFAULT 0.0 NOT NULL,
  humidity REAL DEFAULT 0.0 NOT NULL 
);


DELETE FROM wbd_version;
INSERT INTO wbd_version VALUES(1,'Capture w Ver 1.0','2020-08-11','10');
INSERT INTO wbd_sensor VALUES('DHT22-1','Capteur dht 22');





