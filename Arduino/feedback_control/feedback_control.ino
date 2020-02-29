// Demo for getting individual unified sensor data from the MPU6050
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
Adafruit_Sensor *mpu_temp, *mpu_accel, *mpu_gyro;


double a, sum=0, v=0, init_a=0, tmp, tmp_a=0;
int i=1;

float Kp = 182.946985924925;
float Ki = 7.0383050819117;
float Kd = -223.583790055285;

float input_v=50;
float measured_v, tmp_v=0;

double t=0.01;
double PControl, IControl, DControl, PIDControl;
double error, errorPrevious=input_v;
int pwm_in;

void setup(void) {
  Serial.begin(115200);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");

  mpu_accel = mpu.getAccelerometerSensor();
  mpu_accel->printSensorDetails();
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  for(int i=0; i<10; i++){
      sensors_event_t accel;
      mpu_accel->getEvent(&accel);
      tmp=accel.acceleration.z;
      init_a+=tmp;
  }
  init_a=init_a/10;

  Serial.print("init_a: "); Serial.println(init_a);
  
  delay(5000);
}

void loop() {
  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  mpu_accel->getEvent(&accel);

  /* Display the results (acceleration is measured in m/s^2) */
  
  Serial.print("Accel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" Y: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" Z: ");
  Serial.print(accel.acceleration.z);
  
  
  
/*
  
  analogWrite(5, 150);
  analogWrite(6, 0);

  analogWrite(2, 0);
  analogWrite(3, 150);
  */

  /*
  a=accel.acceleration.x*accel.acceleration.x+accel.acceleration.y*accel.acceleration.y+accel.acceleration.z*accel.acceleration.z;
  a=sqrt(a);
  */
  a=accel.acceleration.z-init_a;

  a=(tmp_a*i+a)/(i+1);  //칼만필터 on
  tmp_a=a;
  
  v=v+a*t; //t

  measured_v=v*18.62607;   //칼만 필터가 없을 때
  

  
  error=input_v-measured_v;

  PControl=Kp*error;
  IControl=Ki*error*t;
  DControl=Kd*(error-errorPrevious)/t;

  PIDControl=PControl+IControl+DControl;

  if(PIDControl<=33 && PIDControl>=0)
    pwm_in=100;
  else if(PIDControl>33 && PIDControl<=58)
    pwm_in=5.8962*PIDControl-90.2547;
  else if(PIDControl<0)
    pwm_in=0;
  else
    pwm_in=255;

  
  analogWrite(5, pwm_in);
  analogWrite(6, 0);

  analogWrite(2, 0);
  analogWrite(3, pwm_in);  
  
  errorPrevious=error;


  
  Serial.print("  a: "); Serial.print(a);
  Serial.print(" measured v: "); Serial.print(measured_v); Serial.print(" pwm_in:"); Serial.print(pwm_in); 
  Serial.print(" PIDControl: "); Serial.print(PIDControl);
  Serial.print(" error: "); Serial.print(error);
  Serial.print(" v: "); Serial.println(v); 
  
  i++;
  
  
  if(i>100){
    analogWrite(5, 0);
    analogWrite(6, 0);

    analogWrite(2, 0);
    analogWrite(3, 0);
    while(1); 
  }
  

  
  delay(t*1000);

  /*   serial plotter friendly format
  Serial.print(temp.temperature);
  Serial.print(",");

  Serial.print(accel.acceleration.x);
  Serial.print(","); Serial.print(accel.acceleration.y);
  Serial.print(","); Serial.print(accel.acceleration.z);
  Serial.print(",");

  Serial.print(gyro.gyro.x);
  Serial.print(","); Serial.print(gyro.gyro.y);
  Serial.print(","); Serial.print(gyro.gyro.z);
  Serial.println();
  delay(10);
  */
}
