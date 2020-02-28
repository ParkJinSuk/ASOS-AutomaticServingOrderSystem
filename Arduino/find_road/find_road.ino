/* 프로그램 내용 : 라인트레이서 모듈을 이용하여 길을 찾는 알고리즘
 * 
 * 라인트레이서 모듈에는 5개의 IR 센서가 존재하는데 그중에서
 * 가운데의 3개는 직선 길을 찾는데 사용하고
 * 가장자리 2개는 커브길의 존재를 탐지하는데 사용
 * 
 * 식당 내부의 길이 road.png 라고 가정할 때,
 * n번 테이블 : 직진 - 좌회전 - 직진 - (n번째 우회전 길에서 )우회전 - 직진
 * 
 * 
 * 프로그램 작성 날짜 : 2020년 2월 27일
 * 
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

int   target_table;

unsigned long time; // 시간 측정을 위한 변수

void setup() {
  Serial.begin(9600);
  Serial.println("###### Setup #####");

  time = millis();
}

void loop() {
  
  /* 0.5초마다 라인트레이서 모듈 센서 측정 */
  if((millis() - time)%500 == 0)
  {
    getIRSensor();
  }

}

/* 라인트레이서 모듈 값 읽어오기 */
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

/* 라인트레이서 모듈 값 출력 */
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

/* 서빙할 테이블로 찾아가는 알고리즘 */
void serving_table(int table_number)
{
  
  if (table_number == 1)
  {
    
  }
}

void forward()
{
  Serial.println("forward");
}
void backward()
{
  Serial.println("backward");
}
void turnLeft()
{
  Serial.println("turn left");
}
void turnRight()
{
  Serial.println("turn right");
}
void _stop()
{
  Serial.println("stop");
}
