#include "WiFiEsp.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "SoftwareSerial.h"

  /* Arduino Pin */
#define SS1_LEFT_OUT  A1
#define SS2_LEFT_IN   A2
#define SS4_RIGHT_IN  A3
#define SS5_RIGHT_OUT A4

#define encoderPinA   2
#define encoderPinB   3

#define MotorA1       5
#define MotorA2       6
#define MotorB1       10
#define MotorB2       11




#define TURN_SPEED  200
#define STRAIGHT_SPEED  110

#define STRAIGHT_SPEED_STRONG  200
#define STRAIGHT_SPEED_WEEK  110

#define SENSING_PERIOD  100

/* global variable - IR sensor */
byte  LeftOut;
byte  LeftIn;
byte  RightIn;
byte  RightOut;

/* global variable - ServingRobot Direction */
int cmd_direction = 0;
int cnt_isRoad = 0;

/* 서빙로봇 명령 */
const int STOP      = 0;
const int LEFT      = 1;
const int STRAIGHT  = 2;
const int RIGHT     = 3;
const int BACK      = 4;
const int FORWARD_THROUGH_CROSSWALK = 5;


/* global variable - PID Control */
long encoderPos = 0;
double angle = 0, angle_pre=0;
int time1 = 0;
int value = 0;

double v;
double v_pre = 0;


float Kp = 4.2227;
float Ki = 2.29743;
float Kd = -0.03976;
float Ke = 0.084;

/*
float Kp = 1.674;
float Ki = 0.8239;
float Kd = -0.3584;
float Ke = 0.084;
*/
int k = 0;

double PControl, IControl=0, DControl, PIDControl;
double error, error_pre;
int pwm_in;

/* global variable - WiFi */
long target_table = 0;

/* global variable - Find Table */
int crosswalk[9] = {0, 1, 1, 2, 2, 3, 3, 4, 4};//갈림길 지나야하는 횟수. index 0은 사용하지 않는다.
int turn[9] = {0, LEFT, RIGHT, LEFT, RIGHT, LEFT, RIGHT, LEFT, RIGHT};//회전해야할 때, left로 가야하는지 right로 가야하는지
int crosswalkCnt = 0;//몇 번째 갈림길을 만났는지 체크!
bool isDone = true;

WiFiEspClient client;
MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);
MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

SoftwareSerial esp(8, 9); // RX, TX


byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(106,10,49,227);  // IP of the MySQL *server* here
char user[] = "sexymandoo";              // MySQL user login username
char password[] = "sexymandoo";        // MySQL user login password

char ssid[] = "Sexy_Jaewon";             // 공유기 이름 SSID
char pass[] = "jaewonsexy";        // 공유기 암호 Password


// Sample query
char query[] = "SELECT _table FROM project.orderDB WHERE call_arduino = '1' AND serving = '0' ;";
char query2[] = "UPDATE project.orderDB SET serving = '1' WHERE call_arduino = '1' AND serving = '0' ;";


int status = WL_IDLE_STATUS;        // Status






int Hz = 20;
unsigned long time; // 시간 측정을 위한 변수


void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  
  Serial.begin(9600);
  esp.begin(9600);
  time = millis();

  WiFi.init(&esp);

    if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  // 와이파이 접속여부 확인
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  // 와이파이 접속정보
  Serial.println(F("You're connected to the network"));
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  long rssi = WiFi.RSSI();
 
  Serial.println(F("Connecting to the server"));


  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    Serial.println(F("Connected to the server"));
  }
  else
    Serial.println(F("Server connection failed."));


}

void loop() {
  
  if(target_table == 0){
    get_table_number();
    isDone = false;
    crosswalkCnt = 0; 
  }
  if(target_table != 0)
  {
    lineTracing();
  }
  if(isDone && (target_table != 0))
  {
    cur_mem->execute(query2); //MySQL에 서빙 완료를 알림
    cur.close();
    target_table = 0;
  }
  
  


  
  //pidControl_Hz(Hz, 30); // 30cm/s 속도로 주행
}

void get_table_number()
{
  row_values *row = NULL;
  target_table = 0;

  delay(1000);

  
 
  cur_mem = new MySQL_Cursor(&conn);
  // query를 실행시켜서 MySQL에서 데이터를 읽어옴
  cur_mem->execute(query);
  column_names *columns = cur_mem->get_columns();

  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      
      target_table = atol(row->values[0]);
    }
  } while (row != NULL);
  // 동적 메모리 할당 지우기
  delete cur_mem;

  // 결과 출력
  Serial.print(F(" 서빙테이블 = "));
  Serial.println(target_table);

  delay(500);
}
