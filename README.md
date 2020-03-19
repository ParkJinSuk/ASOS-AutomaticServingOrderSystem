#1.1 프로젝트 명 

Automatic Serving & Order System 

#1.2 프로젝트 기간 

2020.02.21 ~ 2020.03.21 (4주) 

# RestaurantsSurvingRobot
```
ParkJinSuk
```
ArduinoProject

# IR Sensor
vcc는 5v 전원연결


# WIFI config

WiFiNiNa 라이브러리 추가

# Arduino to Mysql


# MySQL 명령어 모음

Column 이름 변경
```
ALTER TABLE `project`.`orderDB` 
CHANGE COLUMN `order` `_order` INT(11) NOT NULL AUTO_INCREMENT ,
CHANGE COLUMN `table` `_table` INT(11) NOT NULL ;
```
