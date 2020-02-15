#include <SoftwareSerial.h>
#define DEBUG true
#define ledPin 13

uint8_t pin_val = 0; // 디지털 버튼 제어용 변수
uint16_t pwm1 = 0;   // pwm 제어용 변수
uint16_t pwm2 = 0;
uint16_t pwm3 = 0;
String text = "";
char connectionId; // 연결 id 저장 변수
String income_wifi = "";
 
SoftwareSerial esp01(2,3); 
 
void setup() {
  Serial.begin(9600);
  esp01.begin(9600); // your esp's baud rate might be different
  pinMode(ledPin, OUTPUT);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point (working mode: AP+STA)
  sendData("AT+CWSAP=\"ESP-01\",\"1234test\",11,0\r\n",1000,DEBUG); // join the access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop() {
  wifi_delay();
}

unsigned long int one_millis = 0;

void wifi_delay() { // 100 millis
  if (millis() - one_millis > 50) {
    one_millis = millis();
    if (connectionId == '0') esp01.write("AT+CIPCLOSE=0\r\n");
    else if (connectionId == '1') esp01.write("AT+CIPCLOSE=1\r\n");
    else if (connectionId == '2') esp01.write("AT+CIPCLOSE=2\r\n");
    else if (connectionId == '3') esp01.write("AT+CIPCLOSE=3\r\n");
    else if (connectionId == '4') esp01.write("AT+CIPCLOSE=4\r\n");
    wifi_read();
  }
}

void wifi_read() {
    if (esp01.available()) { // check if the esp is sending a message
    if (esp01.find("+IPD,")) {
      income_wifi = esp01.readStringUntil('\r');
      connectionId = income_wifi.charAt(0);
      if (income_wifi.indexOf("%%F1") != -1) {
        if (income_wifi.indexOf("%%F0") != -1) {
          String wifi_temp = income_wifi.substring(income_wifi.indexOf("%%F0")+4, income_wifi.indexOf("%%F1"));
          pin_val = wifi_temp.toInt();
          pin_control();
        }
        else if (income_wifi.indexOf("%%F31") != -1) {
          String wifi_temp = income_wifi.substring(income_wifi.indexOf("%%F31")+5, income_wifi.indexOf("%%F1"));
          pwm1 = wifi_temp.toInt();
          Serial.print("pwm1: "); Serial.println(pwm1);
        }
        else if (income_wifi.indexOf("%%F32") != -1) {
          String wifi_temp = income_wifi.substring(income_wifi.indexOf("%%F32")+5, income_wifi.indexOf("%%F1"));
          pwm2 = wifi_temp.toInt();
          Serial.print("pwm2: "); Serial.println(pwm2);
        }
        else if (income_wifi.indexOf("%%F33") != -1) {
          String wifi_temp = income_wifi.substring(income_wifi.indexOf("%%F33")+5, income_wifi.indexOf("%%F1"));
          pwm3 = wifi_temp.toInt();
          Serial.print("pwm3: "); Serial.println(pwm3); 
        }
      }
      else {
        String wifi_temp = income_wifi.substring(income_wifi.indexOf("GET /")+5, income_wifi.indexOf("HTTP/1.1")-1);
        if (wifi_temp.indexOf("%20") != -1) {
          String space = "%20";
          String space_convert = " ";
          wifi_temp.replace(space, space_convert);
        }
        text = wifi_temp;
        Serial.println(text);
      }
      income_wifi = "";
    }
  }
}
 
String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  esp01.print(command); // send the read character to the esp01
  long int time = millis();
  while( (time+timeout) > millis()) {
    while(esp01.available()) {  // The esp has data so display its output to the serial window 
      char c = esp01.read(); // read the next character.
      response+=c;
    }
  }
  if(debug) Serial.print(response);
  return response;
}

void pin_control() {
  if (pin_val != 0) {
    switch (pin_val) {
      case 11: digitalWrite(ledPin, true); // button 1 : on
                  break;
      case 10: digitalWrite(ledPin, false); // button 1 : off
                  break;
      case 21: Serial.println("button 2 : on");
                  break;
      case 20: Serial.println("button 2 : off");
                  break;
      case 31: Serial.println("button 3 : on");
                  break;
      case 30: Serial.println("button 3 : off");
                  break;
      case 41: Serial.println("button 4 : on");
                  break;
      case 40: Serial.println("button 4 : off");
                  break;
      case 51: Serial.println("button 5 : on");
                  break;
      case 50: Serial.println("button 5 : off");
                  break;
      case 61: Serial.println("button 6 : on");
                  break;
      case 60: Serial.println("button 6 : off");
                  break;
      case 71: Serial.println("button 7 : on");
                  break;
      case 70: Serial.println("button 7 : off");
                  break;
      case 81: Serial.println("button 8 : on");
                  break;
      case 80: Serial.println("button 8 : off");
                  break;
      case 91: Serial.println("button 9 : on");
                  break;
      case 90: Serial.println("button 9 : off");
                  break;  
      case 101: Serial.println("button 10 : on");
                  break;
      case 100: Serial.println("button 10 : off");
                  break;  
      case 111: Serial.println("button 11 : on");
                  break;
      case 110: Serial.println("button 11 : off");
                  break;  
      case 121: Serial.println("button 12 : on");
                  break;
      case 120: Serial.println("button 12 : off");
                  break;  
    }
  pin_val = 0;
  }
}
