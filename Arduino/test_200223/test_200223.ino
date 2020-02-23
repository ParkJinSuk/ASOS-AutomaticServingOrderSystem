/*
  MySQL Connector/Arduino Example : connect by wifi

  This example demonstrates how to connect to a MySQL server from an
  Arduino using an Arduino-compatible Wifi shield. Note that "compatible"
  means it must conform to the Ethernet class library or be a derivative
  thereof. See the documentation located in the /docs folder for more
  details.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Change the SSID and pass to match your WiFi network
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  If you do not see messages indicating you have a connection, refer to the
  manual for troubleshooting tips. The most common issues are the server is
  not accessible from the network or the user name and password is incorrect.

  Note: The MAC address can be anything so long as it is unique on your network.

  Created by: Dr. Charles A. Bell
*/
#include "WiFi.h"                  // Use this for WiFi instead of Ethernet.h
#include "MySQL_Connection.h"
#include "MySQL_Cursor.h"

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(106,10,39,5);  // IP of the MySQL *server* here
char user[] = "sexymandoo";              // MySQL user login username
char password[] = "sexymandoo";        // MySQL user login password

// WiFi card example
char ssid[] = "pink";    // your SSID
char pass[] = "sexymandoo";       // your SSID Password
int status = WL_IDLE_STATUS;
int keyindex;

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  if(WiFi.status() == WL_NO_SHIELD){
    Serial.println("WiFi shield not present");
    while(true);
  }
  while (status != WL_CONNECTED){
    Serial.print("Attempting to connect to WPA SSID:");
    Serial.println(ssid);
    status = WiFi.begin(ssid,pass);

    delay(5000);
  }

  Serial.println("You're connected to the network");

  Serial.println("Connecting to the server...");
  if (conn.connect(server_addr, 9999, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}

void loop() {
}
