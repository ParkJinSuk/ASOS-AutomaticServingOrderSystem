#include "WiFiEsp.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include "SoftwareSerial.h"
SoftwareSerial esp(8, 9); // RX, TX


byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(106,10,49,227);  // IP of the MySQL *server* here
char user[] = "sexymandoo";              // MySQL user login username
char password[] = "sexymandoo";        // MySQL user login password

char ssid[] = "pink";             // 공유기 이름 SSID
char pass[] = "sexymandoo";        // 공유기 암호 Password


// Sample query
char query[] = "SELECT _table FROM project.orderDB WHERE call_arduino = '1' AND serving = '0' ;";
char query2[] = "UPDATE project.orderDB SET serving = '1' WHERE call_arduino = '1' AND serving = '0' ;";


int status = WL_IDLE_STATUS;        // Status

WiFiEspClient client;


MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);

void setup()
{
  Serial.begin(9600);
  esp.begin(9600);

  // 시리얼모니터가 실행될때까지 대기
//  while (!Serial);

  WiFi.init(&esp);

  // 쉴드 존재유무 확인
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true);
  }

  // 와이파이 접속여부 확인
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  // 와이파이 접속정보
  Serial.println("You're connected to the network");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println();

  Serial.println("Connecting to the server");


  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    Serial.println("Connected to the server");
  }
  else
    Serial.println("Server connection failed.");
  //conn.close();

}

void loop()
{
   row_values *row = NULL;
  long head_count = 0;

  delay(1000);

  Serial.println("1) Demonstrating using a cursor dynamically allocated.");
  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(query);
  // Fetch the columns (required) but we don't use them.
  column_names *columns = cur_mem->get_columns();

  // Read the row (we are only expecting the one)
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);
  // Deleting the cursor also frees up memory used
  delete cur_mem;

  // Show the result
  Serial.print(" 서빙테이블 = ");
  Serial.println(head_count);

  delay(500);
/*
  Serial.println("2) Demonstrating using a local, global cursor.");
  // Execute the query
  cur.execute(query);
  // Fetch the columns (required) but we don't use them.
  cur.get_columns();
  // Read the row (we are only expecting the one)
  do {
    row = cur.get_next_row();
    if (row != NULL) {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);
  */
  // Now we close the cursor to free any memory



  cur_mem->execute(query2); //제일 마지막에 해줘야하는 작업
  cur.close();



}
