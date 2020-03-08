// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

long encoderPos = 0;
int angle = 0;
int time1 = 0;
int value = 0;

double v;

float Kp = 4.2227;
float Ki = 2.29743;
float Kd = -0.03976;
float Ke = 0.084;

float input_v=35;

double t=0.01;
double PControl, IControl, DControl, PIDControl;
double error, errorPrevious=input_v;
int pwm_in;

void setup(void) {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  Serial.begin(115200);
  
  pinMode(5, OUTPUT);       // Motor B 방향설정1
  pinMode(6, OUTPUT);       // Motor B 방향설정2


  Serial.println("Starting..");
  motorA(0, 0);
  delay(2000);
  time1 = millis();

  value = 207;
  Serial.print("start speed : ");
  Serial.println(value);
  motorA(1, value);
}

void loop() {
  if( millis()%10 == 0){
    pos2ang();
    
    v=3.15*angle;    
    error=(input_v-v)*Ke;

    PControl=Kp*error;
    IControl=Ki*error*t;
    DControl=Kd*(error-errorPrevious)/t;

    PIDControl=PControl+IControl+DControl;

    pwm_in=255/6*PIDControl;
    Serial.println(pwm_in);
    motorA(1, pwm_in);
    errorPrevious=error;
  }
}


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
  angle = encoderPos/(341.2*4) * 360    /360*2*3.141592;
}
