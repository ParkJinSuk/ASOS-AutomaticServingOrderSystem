#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0x84, 0x0D, 0x8E, 0x34, 0x06, 0xF8 };

IPAddress server_addr(106,10,39,5);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "sexymandoo";        // MySQL user login password

// WiFi card example
char ssid[] = "pink";    // your SSID
char pass[] = "sexymandoo";       // your SSID Password

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  int status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // print out info about the connection:
  else {
    Serial.println("Connected to network");
    IPAddress ip = WiFi.localIP();
    Serial.print("My IP address is: ");
    Serial.println(ip);
  }
  // End WiFi section

  Serial.println("Connecting...");
  if (conn.connect(server_addr, 9999, user, password)) {
    Serial.println("Sex");
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}

void loop() {
}
