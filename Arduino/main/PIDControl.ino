void pidControl_Hz(double Hz, double input_v)
{
  double t = 1 / Hz;
  if( (millis()-time) % (int)(1000 / Hz) == 10 ){
    
    error=(input_v-v)*Ke;
    PControl=Kp*error;
    //if(IControl <= 4){IControl+=Ki*error*t;} //Windup 방지
    IControl+=Ki*error*t;
    DControl=Kd*(error-error_pre)/t;

    PIDControl=PControl+IControl+DControl;
    
    pwm_in=255/6*PIDControl;
    if(pwm_in>=255){pwm_in=255;}

    
    Serial.print("pwm_in: "); Serial.print(pwm_in);
    Serial.print(" v:"); Serial.println(v);
    Serial.print(" error:"); Serial.print(error/Ke);
    Serial.print(" PIDControl: "); Serial.print(PIDControl);
    Serial.print(" P:"); Serial.print(PControl);
    Serial.print(" I:"); Serial.print(IControl);
    Serial.print(" D:"); Serial.println(DControl);
    
    
    
    
    MotorA(Straight, pwm_in);
    MotorB(Straight, pwm_in);
    
    error_pre=error;
  }
}
