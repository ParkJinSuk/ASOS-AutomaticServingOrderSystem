/*  프로그램 내용 : bfd-1000 IR센서 관련 함수
 *  
 *  getIRSensor         IR센서 값 읽어오는 함수
 *  getIRSensor_Hz      주어진 Hz 속도로 IR센서 값 읽어오는 함수
 *  showIRSensorChar    IR센서 값을 문자로 시리얼모니터로 출력해주는 함수
 *  showIRSensorValue   IR센서 값을 시리얼모니터로 출력해주는 함수
 *  
 */

void getIRSensor()
{
  LeftOut  = digitalRead(SS1_LEFT_OUT);
  LeftIn   = digitalRead(SS2_LEFT_IN);
  //Center   = digitalRead(SS3_CENTER);
  RightIn  = digitalRead(SS4_RIGHT_IN);
  RightOut = digitalRead(SS5_RIGHT_OUT);
  //Bump     = digitalRead(CLP_BUMP);
  //Near     = digitalRead(NEAR);
}

void getIRSensor_Hz(int Hz)
{
  if( (millis()-time) % (1000 / Hz) == 0 )
  {
    getIRSensor();
  }
}

void showIRSensorChar()
{
  if (LeftOut  == 1) {Serial.print("L ");} else {Serial.print("- ");}
  if (LeftIn   == 1) {Serial.print("l ");} else {Serial.print("- ");}
  //if (Center   == 1) {Serial.print("C ");} else {Serial.print("- ");}
  if (RightIn  == 1) {Serial.print("r ");} else {Serial.print("- ");}
  if (RightOut == 1) {Serial.print("R ");} else {Serial.print("- ");}
  //if (Bump     == 1) {Serial.print(" BUMP!");} else {Serial.print("      ");}
  //if (Near     == 1) {Serial.print(" NEAR");}  else {Serial.print("    ");}
  Serial.println();
}

void showIRSensorValue()
{
  Serial.print("IRSensor : ");
  Serial.print(LeftOut);Serial.print(LeftIn);
  Serial.print(RightIn);Serial.print(RightOut);
  Serial.println();
}
