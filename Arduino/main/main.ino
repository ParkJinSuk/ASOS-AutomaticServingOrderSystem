/* Arduino Pin */
#define SS1_LEFT_OUT  A1
#define SS2_LEFT_IN   A2
//#define SS3_CENTER
//#define CLP_BUMP
#define SS4_RIGHT_IN  A3
#define SS5_RIGHT_OUT A4
//#define NEAR

/* global variable - IR sensor */
byte  LeftOut;
byte  LeftIn;
//byte  Center;
byte  RightIn;
byte  RightOut;
//byte  Bump;
//int   Near;

unsigned long time; // 시간 측정을 위한 변수


void setup() {
  Serial.begin(9600);

}

void loop() {
  getIRSensor_Hz(20); // IR센서 측정 속도
  
}
