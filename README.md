# Project Name 

ASOS
Automatic Serving & Order System 

# Project Period & Team members

2020.02.21 ~ 2020.03.21 (4주) 
시립대 박진석, 서재원, 송태헌

# Summary

This project creates an unmanned serving robot that automatically serves in a restaurant, an application that places an order, and a web page capable of serving and ordering. Since the serving robot is connected to Wi-Fi, the environment is possible wherever the router is installed, and the ordered food is stored on the server, thus realizing the perfect IoT.


# MySQL 명령어 모음

Column 이름 변경
```
ALTER TABLE `project`.`orderDB` 
CHANGE COLUMN `order` `_order` INT(11) NOT NULL AUTO_INCREMENT ,
CHANGE COLUMN `table` `_table` INT(11) NOT NULL ;
```
