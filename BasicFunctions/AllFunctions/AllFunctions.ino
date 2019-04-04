/*   ----- LIBRARIES -----    */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

/*     DEFINING CONSTANTS     */
/* --------- Motors --------- */ 
//Set up for number 08
#define motorLeft 3
#define motorLeftBack 2
#define motorRight 9
#define motorRightBack 4
/* ------ Ultra sonic ------  */  
#define trigPin 13
#define echoPin 12
/* ----- Light sensors -----  */
#define LS  10    // left sensor 
#define RS  11    // right sensor 

/*     DEFINING IN/OUTPUTS    */
void setup() {
  Serial.begin (9600);
  /* -------- Motors -------- */ 
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorLeftBack, OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  /* ------ Ultra sonic ------  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  /* ---------- LCD ----------  */
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Awaiting orders!");
  delay(1000);
  /* ----- Light sensors -----  */
  pinMode(LS, INPUT); 
  pinMode(RS, INPUT);
}


/*           FUNCTIONS          */
/* --- stopping all motors ---  */
void halt(){
  analogWrite(motorLeftBack, 0);
  analogWrite(motorRightBack, 0);
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  delay(1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stop!");
}

/* Just to clarify: 
 * 'speed' and 'time' seem to have some other use and so in the following I chose speeed and timey instead.
 * So we should not get any problems with that. #safetyFirst :)
 */

/* ----- moving forward -----   */
void forward(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wiu wiu wiu!"); 
    analogWrite(motorLeft, speeed);
    analogWrite(motorRight, speeed);
    delay(timey); 
  } 
}

/* ----- moving backwards ----- */
void backwards(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Beep beep beep!");
    analogWrite(motorLeftBack, speeed);
    analogWrite(motorRightBack, speeed);
    delay(timey);
  } 
}

/* -- turning right on spot --  */
void turnRight(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    lcd.clear();
    lcd.setCursor(0, 0);
    //I wish we had LEDs on both sides of the arduino, like the indicators on a car :3
    lcd.print("To the right!"); 
    analogWrite(motorLeft, speeed);
    analogWrite(motorRightBack, speeed);
    delay(timey);
  } 
}

/* --- turning left on spot --- */
void turnLeft(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("To the left!");
    analogWrite(motorRight, speeed);
    analogWrite(motorLeftBack, speeed);
    delay(timey);
  } 
}

/* -- turning right 90 degr --  */
void right90(){
  turnRight(255, 350);
}

/* --- turning left 90 degr --- */
void left90(){
  turnLeft(255, 350);
}

/* ---- measuring distance ---- */
long duration, distance;
void getDistance(){
  duration = 0;
  distance = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  delay(20);
}

/* -- determining direction --  */
int index = 0;
void getDirection(){
  if(index == 0){
    turnLeft(255, 30);
  }
  else{
    turnRight(255, 30);
  }
}

/*            MODES             */
/* ------ manual control ------ */
void manual(){
}
/* -------- waypoints --------  */
void waypoints(){
}
/* ----- Follow line mode ----- */
void followLine(){
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==LOW)){
    forward(100, 50);
  }
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==HIGH)){
    halt();
  }
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==HIGH)){
    turnLeft(100, 50);
  }
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==LOW)){
    turnRight(100, 50);
  }
}

/* ---- Obstacle Race mode ---- */
void obstacleRace(){
  int timeTurned = 0;
  getDistance();
  while(distance > 30){
    forward(255, 50);
    getDistance();
  }
  halt();
  backwards(255, 30);
  while(distance <= 30){
    getDirection();
    timeTurned += 30;
    if((timeTurned > 350)){
      if(index == 0){
        right90();
        index = 1; 
      }
      else{
        left90();
        index = 0;
      }     
      timeTurned = 0;
    }
    getDistance();
  }
  /* Not necessary I think... We can try out if it makes a difference.
   * 
   *  for(int i = 0; i < 3; i++){
   *    getDistance();
   *    if(distance > 30){
   *      forward(255, 50);
   *    }
   *  }
   *  getDistance();
   */
}

/* ----- determining mode ----- */
int getMode(){
  // Get input from server...?
  // Determin mode: 1 = manual, 2 = waypoints, 3 = followLine, 4 = obstacleRace, anything else = halt;
  int mode = 0;
  return mode;
}

/* ------ Executing loop ------ */
void loop(){
  int mode = getMode();
  switch(mode){
    case 1:
      manual();
      break;
    case 2:
      waypoints();
      break;
    case 3:
      followLine();
      break;
    case 4:
      obstacleRace();
      break;
    default:
      halt();
      break;
  }
}