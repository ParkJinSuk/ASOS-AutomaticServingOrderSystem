void pidControl_Hz(int Hz, double input_v)
{
  double t = 0.1;
  pos2ang(); // 회전 각도 측정(라디안)
  v = 3.15*(angle-angle_pre)/t;
  angle_pre = angle;

  
  error=(input_v-v)*Ke;
  PControl=Kp*error;
  if(IControl <= 4){IControl+=Ki*error*t;} //Windup 방지
  //IControl+=Ki*error*t;
  DControl=Kd*(error-error_pre)/t;

  PIDControl=PControl+IControl+DControl;
  
  pwm_in=255/6*PIDControl;
  if(pwm_in>=255){pwm_in=255;}
  else if(pwm_in<=60){pwm_in=60;}
  
  
  Serial.print("pwm_in: "); Serial.print(pwm_in);
  Serial.print(" v:"); Serial.print(v);
  Serial.print(" error:"); Serial.print(error/Ke);
  Serial.print(" PIDControl: "); Serial.print(PIDControl);
  Serial.print(" P:"); Serial.print(PControl);
  Serial.print(" I:"); Serial.print(IControl);
  Serial.print(" D:"); Serial.println(DControl);
  
  
  //Serial.println(v);

  MotorA(STRAIGHT, pwm_in);
  MotorB(STRAIGHT, pwm_in);
  //MotorA(STRAIGHT, -50);
  //MotorB(STRAIGHT, -50);
  
  //angle_pre = angle;
  v_pre     = v;
  error_pre = error;
}
