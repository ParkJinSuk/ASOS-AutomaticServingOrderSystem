// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

long encoderPos = 0;
int angle = 0;
int time1 = 0;
int value = 0;

void doEncoderA(){ // 빨녹일 때
//  if(digitalRead(encoderPinA)==digitalRead(encoderPinB)) // 같으면
//    encoderPos++; // 정회전
//  else // 다르면
//    encoderPos--; // 역회전
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;
  //Serial.print("A   ");
  //Serial.println(encoderPos);
}

void doEncoderB(){ // 보파일 때
//  if(digitalRead(encoderPinA)==digitalRead(encoderPinB)) // 같으면
//    encoderPos--; // 역회전
//  else // 다르면
//    encoderPos++; // 정회전
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;
  //Serial.print("B   ");
  //Serial.println(encoderPos);
}

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  Serial.begin(115200);

  pinMode(9, OUTPUT);       // Motor B 방향설정1
  pinMode(10, OUTPUT);       // Motor B 방향설정2



  Serial.println("ready");
  motorA(0, 0);
  delay(2000);
  time1 = millis();

  value = 207;
  Serial.print("start speed : ");
  Serial.println(value);
  motorA(1, value);
  
}

void loop() {
  if ((millis() - time1) > 20000)
  {
    pos2ang();
    Serial.print("20second => angle : ");
    Serial.println(angle);
    motorA(0, 0);
    delay(100000);
  }
}

void motorA(int dir, int _speed)
{
  if (dir == 1)
  {
    analogWrite(9, 0);
    analogWrite(10, _speed);
  }
  else if (dir == 2)
  {
    analogWrite(9, _speed);
    analogWrite(10, 0);
  }
  else
  {
    analogWrite(9, 0);
    analogWrite(10, 0);
  }
}

void pos2ang()
{
  angle = encoderPos/(341.2*4) * 360;
}
