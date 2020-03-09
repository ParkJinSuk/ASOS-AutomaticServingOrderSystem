/* 프로그램 내용 : 라인트레이서 모듈을 이용하여 길을 찾는 알고리즘
 * 
 * 라인트레이서 모듈에는 5개의 IR 센서가 존재하는데 그중에서
 * 인식이 잘 안되고 있는 가운데 모듈은 제외하고
 * 가운데 2개는 직선 길을 찾는데 사용하고
 * 가장자리 2개는 커브길의 존재를 탐지하는데 사용
 * 
 * forward        검은색 선을 따라가는 함수
 */

/* 라인트레이서 모듈을 사용하여 검은색 선을 따라가는 함수 */
void forward()
{
  if (!LeftIn && !RightIn)
  {
    Motor_Control(50);
  }
  else if (LeftIn && !RightIn)
  {
    MotorA(Straight, 150);
    MotorB(Straight, 80);
  }
  else if (!LeftIn && RightIn)
  {
    MotorA(Straight, 80);
    MotorB(Straight, 150);
  }
  else if (LeftIn && RightIn)
  {
    MotorA(Stop, 0);
    MotorB(Stop, 0);
  }
  else
  {
    MotorA(Straight, 200);
    MotorB(Straight, 200);
  }
  
  
}
void backward()
{
  MotorA(Back, 150);
  MotorB(Back, 150);
}
void turnLeft()
{
  MotorA(Straight, 200);
  MotorB(Straight, 100);
}
void turnRight()
{
  MotorA(Straight, 100);
  MotorB(Straight, 200);
}
void _stop()
{
  MotorA(Stop, 0);
  MotorB(Stop, 0);
}
