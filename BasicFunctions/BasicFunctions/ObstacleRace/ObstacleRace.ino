
//all motors called analog
//motors set up for number 05
#define motorLeft 2
#define motorLeftBack 3
#define motorRight 4
#define motorRightBack 9  
#define trigPin 13
#define echoPin 12

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Awaiting orders!");
  delay(1000);
}

//stops motors
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

//moves forward
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

//moves backwards
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

//turns right on spot
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

//turns left on spot
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

//turns right 90deg 
void right90(){
  turnRight(255, 350);
}

//turns left 90deg
void left90(){
  turnLeft(255, 350);
}

//measures distance
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

//determines direction to turn
int index = 0;
int timeLeft = 0;
int timeRight = 0;
void getDirection(){
  if(index == 0){
    turnLeft(255, 30);
    timeLeft += 30;
  }
  else{
    turnRight(255, 30);
    timeRight += 30;
  }
}

void loop(){
  int timeTurned = 0;
  timeLeft = 0;
  timeRight = 0;
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
    if((timeTurned >= 600)){
      if(index == 0){
        right90();
        index = 1; 
      }
      else{
        left90();
        index = 0;
      }     
    }
    getDistance();
  }
  for(int i = 0; i < 3; i++){
    getDistance();
    if(distance > 30){
      forward(255, 50);
    }
  }
  getDistance();
}
