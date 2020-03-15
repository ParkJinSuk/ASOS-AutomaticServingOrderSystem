void lineTracing()
{
  /* 0.5초마다 라인트레이서 모듈 센서 측정 */
  if((millis() - time) >= SENSING_PERIOD)
  {
    time = millis();
    getIRSensor();
//    showIRSensor();
    if(isCrosswalk()){
      Serial.println(F("갈림길 감지"));
      crosswalkCnt += 1;
      if(isTurningTime(crosswalkCnt)){//회전할 갈림길
        if(turn[target_table] == LEFT)
          Serial.println(F("왼쪽"));
        else if(turn[target_table] == RIGHT){
          Serial.println(F("오른쪽"));
        }
        moveTracer(turn[target_table]);//회전한다.
      }else{
        Serial.println(F("갈림길 통과"));
        moveTracer(FORWARD_THROUGH_CROSSWALK);//갈림길 통과
      }
      
    }else if(isRoad()){
      Serial.println(F("straight"));
      moveTracer(STRAIGHT);//앞으로 이동.
    }else{
     Serial.println(F("stop"));
      moveTracer(STOP);//멈춘다.
      isDone = true;
    }
  }
  

}

bool isCrosswalk(){
  return !RightOut && !LeftOut;//검검이면 갈림길!!
}

bool isTurningTime(int cnt){
  Serial.println(cnt);
  return cnt == crosswalk[target_table];
}

bool isRoad(){
  if (!LeftOut || !LeftIn || !RightIn || !RightOut)
  {
    cnt_isRoad = 0;
    return true;
  }
  else
  {
    if (cnt_isRoad != 5){cnt_isRoad += 1; return true;}
    if (cnt_isRoad == 5){cnt_isRoad = 0; return false;}
  }  
}

void moveTracer(int dir){
//  Serial.print("moveTracer");
//  Serial.println(dir);

  switch(dir){
    case STRAIGHT  : moveForward();break;
    case LEFT     : turnLeft();break;
    case RIGHT    : turnRight();break;
    case STOP     : stopMoving();break;
    case FORWARD_THROUGH_CROSSWALK : moveThroughCrosswalk();break;
  }
}


/* 라인트레이서 모듈을 사용하여 검은색 선을 따라가는 함수 */
void moveForward()
{
  if (!LeftIn && !RightIn)
  {
//    Serial.println("forward 11");
    pidControl_Hz(Hz, 20);
  }
  else if (LeftIn && !RightIn)
  {
//    Serial.println("forward 01");
    MotorA(STRAIGHT, STRAIGHT_SPEED_WEEK);
    MotorB(STRAIGHT, STRAIGHT_SPEED_STRONG);
  }
  else if (!LeftIn && RightIn)
  {
//    Serial.println("forward 10");
    MotorA(STRAIGHT, STRAIGHT_SPEED_STRONG);
    MotorB(STRAIGHT, STRAIGHT_SPEED_WEEK);
  }
  else
  {
//    Serial.println("forward xx");
    pidControl_Hz(Hz, 20);
  }
  
  
}

void turnLeft()
{
//  Serial.println("turn left");

  while(!RightOut || !LeftOut){//하양이면 끝. 도는 동안은 계속 검정.
    if((millis() - time) >= SENSING_PERIOD){
      time = millis();
      getIRSensor();
    }
    Serial.println(F("왼쪽~~~~~~~~~~~~~~~~"));


    MotorA(STRAIGHT, TURN_SPEED);
    MotorB(STRAIGHT, 0);
  }
   Serial.println(F("왼쪽~~~~~~~~~~~~끝~~~~"));

}
void turnRight()
{
//  Serial.println("turn right");

  while(!RightOut || !LeftOut){//하양이면 끝. 도는 동안은 계속 검정.
    if((millis() - time) >= SENSING_PERIOD){
      time = millis();
      getIRSensor();
    }
//    if(LeftOut != pre){
//      chgCnt += 1;
//      pre = LeftOut;
//    }
    Serial.println(F("오른쪽~"));

    MotorA(STRAIGHT, 0);
    MotorB(STRAIGHT, TURN_SPEED);
  }
   Serial.println(F("오른끝쪽"));


}
void stopMoving()
{
//  Serial.println("stop");
  MotorA(STOP, 0);
  MotorB(STOP, 0);
}

void moveThroughCrosswalk(){
  //    Serial.println("move Through crosswalk");
  while(isCrosswalk()){
    if((millis() - time) >= SENSING_PERIOD){
      time = millis();
      getIRSensor();
    }

    MotorA(STRAIGHT, STRAIGHT_SPEED);
    MotorB(STRAIGHT, STRAIGHT_SPEED);
    delay(100);
  }
}
/****************************/
