void pidControl_Hz(double Hz, double input_v)
{
  double t = 1 / Hz;
  if( (millis()-time) % (int)(1000 / Hz) == 0 ){

    
    v1=v2; v2=v3; v3=v4; v4=v5; v5=v6;
    v6=v7; v7=v8; v8=v9; v9=v10;
    v10=3.15*(angle-anglePrevious)/t;
    v = (v1+v2+v3+v4+v5+v6+v7+v8+v9+v10)/10; //속도는 최근 5개의 값의 평균
    //v = 3.15*(angle-anglePrevious)/t;
    //v = (vPrevious*k+v)/(k+1);
    //vPrevious = v;
    //k++;
    
    
    error=(input_v-v)*Ke;
    PControl=Kp*error;
    //if(IControl <= 4){IControl+=Ki*error*t;} //Windup 방지
    IControl+=Ki*error*t;
    DControl=Kd*(error-errorPrevious)/t;

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
    
    //Serial.println(v);
    MotorA(Straight, pwm_in);
    MotorB(Straight, pwm_in);
    
    errorPrevious=error;
  }
}
