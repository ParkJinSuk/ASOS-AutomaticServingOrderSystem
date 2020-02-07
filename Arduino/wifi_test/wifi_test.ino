#include "WizFi310.h"

char ssid[] = "pink";
char pass[] = "sexymandoo";
int status = WL_IDLE_STATUS; //???

char server[]="arduino.cc";

WiFiClient client;



void printWifiStatus();

void setup() {
  Serial.begin(115200);
  //Serial3.begin(115200);
  WiFi.init(&Serial);

  while ( status != WL_CONNECTED){
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status=WiFi.begin(ssid, pass);
  }
  Serial.println("You are connected to the network.");

  Serial.println();
  Serial.println("Starting connection to server...");
  if(client.connect(server,80)){
    Serial.println("Connected to server");
    client.println("GET /asciilogo.txt HTTP/1.1");
    client.println("Host: arduino.cc");
    client.println("Connection: close");
    client.println();
  }

}

void loop() {
  while (client.available()){
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()){
    Serial.println();
    Serial.println("Disconnecting from sever...");
    client.stop();
    while(true);
  }

}
