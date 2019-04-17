/* ----------------------------------------------------------- LIBRARIES ----------------------------------------------------------- */
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

/* !! SET UP FOR NUMBER 10 !! */
/* ------------------------------------------------------ DEFINING CONSTANTS ------------------------------------------------------  */
/* ------- Bluetooth -------  */
#define RxD A0
#define TxD A1
/* --------- Motors --------- */ 
//motor forward left
#define m_FL 3
#define motorForwardLeft 3
//motor backwards left
#define m_RL 2 
#define motorBackwardsLeft 2
//motor forward right
#define m_FR 9 
#define motorForwardRight 9
//motor backwards right
#define m_RR 4 
#define motorBackwardsRight 4

/* ------ Ultra sonic ------  */  
#define trigPin 13
#define echoPin 12
/* ----- Light sensors -----  */
#define LS  10    // left sensor 
#define RS  11    // right sensor 

SoftwareSerial serial = SoftwareSerial(RxD,TxD);

/* ------------------------------------------------------ DEFINING IN/OUTPUTS ------------------------------------------------------ */
void setup() {
  serial.begin(38400);
  Serial.begin(9600);
  /* -------- Motors -------- */ 
  pinMode(motorForwardLeft, OUTPUT);
  pinMode(motorForwardRight, OUTPUT);
  pinMode(motorBackwardsLeft, OUTPUT);
  pinMode(motorBackwardsRight, OUTPUT);
  pinMode(m_FL, OUTPUT);
  pinMode(m_FR, OUTPUT);
  pinMode(m_RL, OUTPUT);
  pinMode(m_RR, OUTPUT);
  /* ------ Ultra sonic ------  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  /* ---------- lcd ----------  */
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Awaiting orders!");
  /* ----- Light sensors -----  */
  pinMode(LS, INPUT); 
  pinMode(RS, INPUT);
}

/* ----------------------------------------------------------- FUNCTIONS ----------------------------------------------------------- */
/* ------------------------- basic functions ------------------------- */
/* --- stopping all motors ---  */
void halt(){
  analogWrite(motorBackwardsLeft, 0);
  analogWrite(motorBackwardsRight, 0);
  analogWrite(motorForwardLeft, 0);
  analogWrite(motorForwardRight, 0);
  delay(1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stop!");
  lcd.setCursor(0, 1);
  lcd.print("Awaiting orders!");
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
    analogWrite(motorForwardLeft, speeed);
    analogWrite(motorForwardRight, speeed);
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
    analogWrite(motorBackwardsLeft, speeed);
    analogWrite(motorBackwardsRight, speeed);
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
    analogWrite(motorForwardLeft, speeed);
    analogWrite(motorBackwardsRight, speeed);
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
    analogWrite(motorForwardRight, speeed);
    analogWrite(motorBackwardsLeft, speeed);
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

/* ------------------------------------------------------------- MODES ------------------------------------------------------------- */
/* ------------------- functions for game modes ------------------- */
/* ------ Manual control ------ */
void manual(){
}
/* -------- Waypoints --------  */
void waypoints(){
  halt(); //replace with waypoints method
}
/* ----- Follow line mode ----- */
void followLine(){
  int direction;
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==LOW)){
    forward(180, 20);
  }
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==HIGH)){
    if(direction == 1){
      turnLeft(120, 30);
    }
    if(direction == 2){
      turnRight(120, 30);
    }
  }
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==HIGH)){
    direction = 1;
    turnLeft(100, 60);
  }
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==LOW)){
    direction = 2;
    turnRight(100, 60);
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
}

/* --------------------------------------------------------- EXECUTING LOOP -------------------------------------------------------- */
void loop(){
  /* -- determining game mode --   */
  //Get game mode, run appropriate game mode function depending on the game mode. 
}
