#include <WiFi.h>                  // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(106,10,39,5);  // IP of the MySQL *server* here
char user[] = "sexymandoo";              // MySQL user login username
char password[] = "sexymandoo";        // MySQL user login password

// WiFi card example
char ssid[] = "pink";    // your SSID
char pass[] = "sexymandoo";       // your SSID Password

// Sample query
char query[] = "SELECT Num FROM test.test WHERE name = 'sex'";

WiFiClient client;            // Use this for WiFi instead of EthernetClient

MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);

void setup() {
  Serial.begin(115200);

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
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}

void loop() {
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
  Serial.print("  NYC pop = ");
  Serial.println(head_count);

  delay(500);

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
  // Now we close the cursor to free any memory
  cur.close();

  // Show the result but this time do some math on it
  Serial.print("  NYC pop = ");
  Serial.println(head_count);
  Serial.print("  NYC pop increased by 12 = ");
  Serial.println(head_count+12);

}
