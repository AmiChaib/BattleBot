
//all motors called analog
#define motorLeft 3
#define motorLeftBack 2
#define motorRight 9
#define motorRightBack 4  
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

void loop(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  delay(20);
  while(distance > 20){
    forward(255, 100);
  }
  halt();
  int timeTurned = 0;
  while(distance < 20){
    turnLeft(255, 30);
    timeTurned += 30;
    while((timeTurned >= 600) && (timeTurned <= 800)){
      turnLeft(255, 50);
      timeTurned += 50;
    }
  }
  forward(255, 50);
  if(timeTurned < 700){
    turnRight(255, timeTurned);
  }
  else{
    int newTime = 1400 - timeTurned;
    turnLeft(255, newTime);
    newTime = 0;
  }
  timeTurned = 0;
}
