#include <SPI.h>
#include <WiFiNINA.h>

//https://www.elithecomputerguy.com/2019/06/arduino-uno-with-wifi-basic-setup/

char ssid[] = "Inseockjjang";
char pass[] = "029603574";
char command[] = "ls\n";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
  
//char server[] = "http://google.com/";
//DNS를 이용한 accesing을 하고 싶을 때 위의 server 사용

IPAddress server(45,119,146,198);

WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 1 seconds for connection:
    delay(1000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 5000)) {                    //5000번 포트로 연결하기~
    Serial.println("connected to server");
    // Make a HTTP request:
    //client.println("HTTP/1.1 200 OK");
    //client.println("Content-Type: text/html");
    //client.println("GET /search?q=arduino HTTP/1.1");
    //client.println("Host: www.google.com");
    //client.println("Connection: close"); // the connection will be closed after completion of the response
    //client.println("Refresh: 1");  // refresh the page automatically every 1 sec
    //client.println();
    //client.println("<!DOCTYPE HTML>");
    //client.println("<html>");
    //client.println("ls");
  }
}

void loop() {
  while (client.available()) {
    char c = client.read();
    Serial.write(c); //c 출력
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
