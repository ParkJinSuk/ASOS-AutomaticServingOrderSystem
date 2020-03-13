/*  프로그램 내용 : DC Motor 컨트롤하는 함수들
 *  
 *  MotorA              MotorA를 PWM 전압으로 조절하는 함수 
 *  MotorB              MotorB를 PWM 전압으로 조절하는 함수
 *  
 *  doEncoderA          DC모터 엔코더 카운트 하기 위한 함수
 *  doEncoderB          DC모터 엔코더 카운트 하기 위한 함수
 *  pos2ang             엔코더로부터 회전 각도 구하는 함수
 *  pos2ang_Hz          주어진 Hz속도로 회전 각도 구하는 함수
 *  
 */

void MotorA(int dir, int _speed)
{
  if (dir == Straight)
  {
    analogWrite(MotorA1, 0);
    analogWrite(MotorA2, _speed);
  }
  else if (dir == Back)
  {
    analogWrite(MotorA1, _speed);
    analogWrite(MotorA2, 0);
  }
  else
  {
    analogWrite(MotorA1, 0);
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
  else if (dir == Back)
  {
    analogWrite(MotorB1, 0);
    analogWrite(MotorB2, _speed);
  }
  else
  {
    analogWrite(MotorB1, 0);
    analogWrite(MotorB2, 0);
  }
}

void doEncoderA()
{
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;
}

void doEncoderB()
{
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;
}

void pos2ang()
{
  angle = -encoderPos/(341.2*4) * 360 /180*3.141592  ;
}
