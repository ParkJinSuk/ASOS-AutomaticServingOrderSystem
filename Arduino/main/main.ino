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

#define vi            20

/* global variable - IR sensor */
byte  LeftOut;
byte  LeftIn;
byte  RightIn;
byte  RightOut;

/* global variable - ServingRobot Direction */
int cmd_direction = 0;
int Stop          = 0;
int Left          = 1;
int Straight      = 2;
int Right         = 3;
int Back          = 4;

/* global variable - PID Control */
long encoderPos = 0;
double angle = 0, angle_pre=0;
int time1 = 0;
int value = 0;

double v;
double v_pre = 0;
double v_array[10]={0};
float Kp = 4.2227;
float Ki = 2.29743;
float Kd = -0.03976;
float Ke = 0.084;

int k = 0;

double PControl, IControl=0, DControl, PIDControl;
double error, error_pre;
int pwm_in;



unsigned long time; // 시간 측정을 위한 변수

double Hz = 20;

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
  
  Serial.begin(9600);

}

void loop() {
  getIRSensor_Hz(Hz); // IR센서 측정
  pos2ang_Hz(50);     // DC모터 회전 각도 측정

  Motor_Control(vi);
}
