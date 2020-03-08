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

#define MotorA1       3
#define MotorA2       5
#define MotorB1       6
#define MotorB2       9

/* 서빙로봇 */
int Stop      = 0;
int Left      = 1;
int Straight  = 2;
int Right     = 3;
int Back      = 4;

int   route[]= {Stop, Stop, Stop, Stop, Stop};  // 서빙로봇의 경로를 저장
int   stack_right;  // 우회전길이 보일때마다 하나씩 증가
int   cmd;         // 서빙로봇이 나아갈 방향
int   route_target[] = {Straight, Left, Straight, Right, Straight};

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
int           temp;
unsigned long RightTime;

void setup() {
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("###### Setup #####");

  time = millis();

}

void loop() {
  target_table = 1;

  cmd = Straight;
  
  /* 0.5초마다 라인트레이서 모듈 센서 측정 */
  if((millis() - time)%100 == 0)
  {
    getIRSensor();
    //showIRSensor();
  }

  //serving_table(target_table);

  /* 0.5초마다 주행 명령 */
  if((millis() - time)%100 == 0)
  {
    if (cmd == Straight)
    {
      forward();
    }
    
    if (cmd == Left)
    {
      //서빙로봇 좌회전
    }
    
    if (cmd == Right)
    {
      //서빙로봇 우회전
    }
    
    if (cmd == Stop)
    {
      //서빙로봇 정지
    }
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
/********************************/




/* 서빙할 테이블로 찾아가는 알고리즘 */
void serving_table(int table_number)
{
  if (route[0] == Stop)
  {
    cmd = route_target[0]; // 서빙로봇의 방향 결정
    route[0] == route_target[0];
  }
  else if ((route[1] == Stop)  && (LeftOut == true))
  {
    cmd = route_target[1];
    route[1] == route_target[1];
  }
  else if ((route[2] == Stop)  && (LeftOut == false))
  {
    cmd = route_target[2];
    route[2] == route_target[2];
    
    temp = 0;
  }
  else if (route[3] == Stop)
  {
    if ((temp == 0) && RightOut == true)
    {
      RightTime = millis();
      temp = 1;
    }

    if (RightOut == false)
    {
      temp = 0;
    }
    
    if (((RightTime - millis()) > 100) && ((RightTime - millis()) < 1000))
    {
      stack_right += 1;
      temp = 0;
    }
  }
  else if ((route[3] == Stop)  && stack_right == table_number)
  {
    cmd = route_target[3];
    route[3] == route_target[3];
  }
  else if ((route[4] == Stop)  && RightOut == false)
  {
    cmd = route_target[4];
    route[4] == route_target[4];
  }

}
/*************************************/



/* 라인트레이서 모듈을 사용하여 검은색 선을 따라가는 함수 */
void forward()
{
  /*
  if (!LeftIn && !Center && !RightIn)
  {
    Serial.println("forward 111");
    MotorA(Straight, 230);
    MotorB(Straight, 230);
  }
  else if (LeftIn && !Center && !RightIn)
  {
    Serial.println("forward 011");
    MotorA(Straight, 150);
    MotorB(Straight, 210);
  }
  else if (!LeftIn && !Center && RightIn)
  {
    Serial.println("forward 110");
    MotorA(Straight, 210);
    MotorB(Straight, 150);
  }
  else if (LeftIn && Center && RightIn)
  {
    Serial.println("forward 000");
    MotorA(Stop, 0);
    MotorB(Stop, 0);
  }
  else
  {
    Serial.println("forward xxx");
    MotorA(Straight, 200);
    MotorB(Straight, 200);
  }
  */

  if (!LeftIn && !RightIn)
  {
    Serial.println("forward 111");
    MotorA(Straight, 170);
    MotorB(Straight, 170);
  }
  else if (LeftIn && !RightIn)
  {
    Serial.println("forward 011");
    MotorA(Straight, 150);
    MotorB(Straight, 80);
  }
  else if (!LeftIn && RightIn)
  {
    Serial.println("forward 110");
    MotorA(Straight, 80);
    MotorB(Straight, 150);
  }
  else if (LeftIn && RightIn)
  {
    Serial.println("forward 000");
    MotorA(Stop, 0);
    MotorB(Stop, 0);
  }
  else
  {
    Serial.println("forward xxx");
    MotorA(Straight, 200);
    MotorB(Straight, 200);
  }
  
  
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

  MotorA(Stop, 0);
  MotorB(Stop, 0);
}
/****************************/



/* 모터를 직접 컨트롤 하는 함수 */
void MotorA(int dir, int _speed)
{
  if (dir == Straight)
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
  if (dir == Straight)
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
