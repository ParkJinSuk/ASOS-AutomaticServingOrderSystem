const int encoderPinA = 2;
const int encoderPinB = 3;

long encoderPos = 0;
double angle = 0, anglePrevious=0;
int time1 = 0;
int value = 0;

double v;
double v1=0;double v2=0;double v3=0;double v4=0;double v5=0;


float Kp = 4.2227;
float Ki = 2.29743;
float Kd = -0.03976;
float Ke = 0.084;


float input_v=10;

double t=0.05;
double PControl, IControl=0, DControl, PIDControl;
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



  motorA(0, 0);
  delay(2000);
  time1 = millis();

}

void loop() {
  if( millis()% 50 == 0){
    pos2ang();
    
    v1=v2;   
    v2=v3;
    v3=v4;
    v4=v5;
    v5=3.15*(angle-anglePrevious)/t;
    
    v = (v1+v2+v3+v4+v5)/5;
    
    
    
    error=(input_v-v)*Ke;

    PControl=Kp*error;
    IControl+=Ki*error*t;
    DControl=Kd*(error-errorPrevious)/t;

    PIDControl=PControl+IControl+DControl;

    pwm_in=255/6*PIDControl;
    if(pwm_in>=255)
      pwm_in=255;
    /*Serial.print("pwm_in: "); Serial.print(pwm_in);
    Serial.print(" v:"); Serial.println(v);
    Serial.print(" error:"); Serial.print(error/Ke);
    Serial.print(" PIDControl: "); Serial.print(PIDControl);
    Serial.print(" P:"); Serial.print(PControl);
    Serial.print(" I:"); Serial.print(IControl);
    Serial.print(" D:"); Serial.println(DControl);*/
    Serial.println(v);
    motorA(1, pwm_in);
    errorPrevious=error;
    anglePrevious=angle;
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
    analogWrite(5, 0);
    analogWrite(6, _speed);
  }
  else if (dir == 2)
  {
    analogWrite(5, _speed);
    analogWrite(6, 0);
  }
  else
  {
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
}

void pos2ang()
{
  angle = -encoderPos/(341.2*4) * 360 /180*3.141592  ;
}
