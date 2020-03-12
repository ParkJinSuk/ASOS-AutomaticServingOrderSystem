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
#define SS1_LEFT_OUT  A1
#define SS2_LEFT_IN   A2
#define SS4_RIGHT_IN  A3
#define SS5_RIGHT_OUT A4

#define MotorA1       5
#define MotorA2       6
#define MotorB1       10
#define MotorB2       11


/* 서빙로봇 명령 */
const int STOP      = 0;
const int LEFT      = 1;
const int STRAIGHT  = 2;
const int RIGHT     = 3;
const int BACK      = 4;
const int FORWARD_THROUGH_CROSSWALK = 5;

int crosswalk[9] = {0, 1, 1, 2, 2, 3, 3, 4, 4};//갈림길 지나야하는 횟수. index 0은 사용하지 않는다.
int turn[9] = {0, LEFT, RIGHT, LEFT, RIGHT, LEFT, RIGHT, LEFT, RIGHT};//회전해야할 때, left로 가야하는지 right로 가야하는지
int crosswalkCnt = 0;//몇 번째 갈림길을 만났는지 체크!
/* 센서 전역 변수 */
byte  LeftOut;
byte  LeftIn;
byte  RightIn;
byte  RightOut;

int   target_table;
int   cmd;

unsigned long time; // 시간 측정을 위한 변수

void setup() {
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("###### Setup #####");

  time = millis();

  //TODO: wifi로 target_table을 선택해야.
  target_table = 1;
  //TODO: 처음 명령은 STRAIGHT
  cmd = STRAIGHT;

}

void loop() {

  
  /* 0.5초마다 라인트레이서 모듈 센서 측정 */
  if((millis() - time) >= 500)
  {
    time = millis();
    getIRSensor();
    showIRSensor();
  
    if(isCrosswalk()){
      crosswalkCnt += 1;
      if(isTurningTime(crosswalkCnt)){//회전할 갈림길
        moveTracer(turn[target_table]);//회전한다.
      }else{
        moveTracer(FORWARD_THROUGH_CROSSWALK);//갈림길 통과
      }
      
    }else if(isRoad()){
      moveTracer(STRAIGHT);//앞으로 이동.
    }else{
      moveTracer(STOP);//멈춘다.
    }
  }
  

}




/* 라인트레이서 모듈 값 읽어오기 */
void getIRSensor()
{
  LeftOut  = digitalRead(SS1_LEFT_OUT);
  LeftIn   = digitalRead(SS2_LEFT_IN);
  RightIn  = digitalRead(SS4_RIGHT_IN);
  RightOut = digitalRead(SS5_RIGHT_OUT);
}
/* 라인트레이서 모듈 값 출력 */
void showIRSensor()
{
  if (LeftOut  == 1) {Serial.print("L ");} else {Serial.print("- ");}
  if (LeftIn   == 1) {Serial.print("l ");} else {Serial.print("- ");}
  if (RightIn  == 1) {Serial.print("r ");} else {Serial.print("- ");}
  if (RightOut == 1) {Serial.print("R ");} else {Serial.print("- ");}
  Serial.println();
}
/********************************/

bool isCrosswalk(){
  return !RightOut && !LeftOut;//검검이면 갈림길!!
}

bool isTurningTime(int cnt){
  Serial.println(cnt);
  return cnt == crosswalk[target_table];
}

bool isRoad(){
  return !LeftIn || !RightIn;//하나라도 검정이면 길!
}

void moveTracer(int dir){
  Serial.print("moveTracer");
  Serial.println(dir);

  switch(dir){
    case STRAIGHT  : moveForward();break;
    case LEFT     : turnLeft();break;
    case RIGHT    : turnRight();break;
    case STOP     : stopMoving();break;
    case FORWARD_THROUGH_CROSSWALK : moveThroughCrosswalk();break;
  }
}


/* 라인트레이서 모듈을 사용하여 검은색 선을 따라가는 함수 */
void moveForward()
{
  if (!LeftIn && !RightIn)
  {
    Serial.println("forward 111");
    MotorA(STRAIGHT, 170);
    MotorB(STRAIGHT, 170);
  }
  else if (LeftIn && !RightIn)
  {
    Serial.println("forward 011");
    MotorA(STRAIGHT, 150);
    MotorB(STRAIGHT, 80);
  }
  else if (!LeftIn && RightIn)
  {
    Serial.println("forward 110");
    MotorA(STRAIGHT, 80);
    MotorB(STRAIGHT, 150);
  }
  else if (LeftIn && RightIn)
  {
    Serial.println("forward 000");
    MotorA(STOP, 0);
    MotorB(STOP, 0);
  }
  else
  {
    Serial.println("forward xxx");
    MotorA(STRAIGHT, 200);
    MotorB(STRAIGHT, 200);
  }
  
  
}

void turnLeft()
{
  Serial.println("turn left");
  //LEFTOUT이 (검정->)하양->검정->하양일 때까지!
  byte pre = RightOut;
  int chgCnt = 0;

  while(chgCnt < 3){
    if((millis() - time) >= 500){
      time = millis();
      getIRSensor();
    }
    if(RightOut != pre){
      chgCnt += 1;
      pre = RightOut;
    }

    MotorA(STRAIGHT, 0);
    MotorB(STRAIGHT, 150);
  }
}
void turnRight()
{
  Serial.println("turn right");
  //LEFTOUT이 (검정->)하양->검정->하양일 때까지!
  byte pre = LeftOut;
  int chgCnt = 0;

  while(chgCnt < 3){
    if((millis() - time) >= 500){
      time = millis();
      getIRSensor();
    }
    if(LeftOut != pre){
      chgCnt += 1;
      pre = LeftOut;
    }

    MotorA(STRAIGHT, 150);
    MotorB(STRAIGHT, 0);
  }

}
void stopMoving()
{
  Serial.println("stop");
  MotorA(STOP, 0);
  MotorB(STOP, 0);
}

void moveThroughCrosswalk(){
  while(isCrosswalk()){
    Serial.println("move Through crosswalk");
    getIRSensor();//시간제한 넣자.

    MotorA(STRAIGHT, 170);
    MotorB(STRAIGHT, 170);
    delay(100);
  }
}
/****************************/











/* 모터를 직접 컨트롤 하는 함수 */
void MotorA(int dir, int _speed)
{
  if (dir == STRAIGHT)
  {
    analogWrite(MotorA1, 0);
    analogWrite(MotorA2, _speed);
  }
  else
  {
    analogWrite(MotorA1, _speed);
    analogWrite(MotorA2, 0);
  }
}
void MotorB(int dir, int _speed)
{
  if (dir == STRAIGHT)
  {
    analogWrite(MotorB1, _speed);
    analogWrite(MotorB2, 0);
  }
  else
  {
    analogWrite(MotorB1, 0);
    analogWrite(MotorB2, _speed);
  }
}
/*****************************/
