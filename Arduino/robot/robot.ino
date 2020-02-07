/*  프로그램 내용 : 이 로봇은 5개의 IR센서를 사용하여
 *  라인을 트랙킹하며 길을 찾아 서빙을 합니다.
 *  
 *  프로그램 작성 날짜 : 2020년 2월 5일
 *  
 *  [수정날짜0205] - 핀번호 추가
 */

/* 핀번호 설정 */
#define SS1_LEFT_OUT  2
#define SS2_LEFT_IN   4
#define SS3_CENTER    7
#define CLP_BUMP      8
#define SS4_RIGHT_IN  11
#define SS5_RIGHT_OUT 12
#define NEAR          A5

/* 전역 변수 */
byte  LeftOut;
byte  LeftIn;
byte  Center;
byte  RightIn;
byte  RightOut;
byte  Bump;
int   Near;

unsigned long time; // 시간 측정을 위한 변수

void setup() {
  // put your setup code here, to run once:
  Serial.println("### Setup ###");
  Serial.begin(9600);

  time = millis();
}

void loop() {
  if((millis()-time)%1000 == 0)
  {
    getIRSensor();
    showIRSensor();
  }
  
}

void getIRSensor()
{
  LeftOut  = digitalRead(SS1_LEFT_OUT);
  LeftIn   = digitalRead(SS2_LEFT_IN);
  Center   = digitalRead(SS3_CENTER);
  RightIn  = digitalRead(SS4_RIGHT_IN);
  RightOut = digitalRead(SS5_RIGHT_OUT);
  Bump     = digitalRead(CLP_BUMP);
  Near     = digitalRead(NEAR);
}

void showIRSensor()
{
  if (LeftOut  == 1) {Serial.print("L ");} else {Serial.print("- ");}
  if (LeftIn   == 1) {Serial.print("l ");} else {Serial.print("- ");}
  if (Center   == 1) {Serial.print("C ");} else {Serial.print("- ");}
  if (RightIn  == 1) {Serial.print("r ");} else {Serial.print("- ");}
  if (RightOut == 1) {Serial.print("R ");} else {Serial.print("- ");}
  if (Bump     == 1) {Serial.print(" BUMP!");} else {Serial.print("      ");}
  if (Near     == 1) {Serial.print(" NEAR");}  else {Serial.print("    ");}
  Serial.println();
}
