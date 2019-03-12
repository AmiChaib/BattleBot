
//all motors called analog
#define motorLeft 3
#define motorLeftBack 2
#define motorRight 9
#define motorRightBack 4  
#define trigPin 13
#define echoPin 12
#define led NULL
#define led2 NULL

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
  lcd.print("Wiu wiu wiu!");
  delay(1000);
}

/*void loop(){
  analogWrite(motorRight, 255);
  analogWrite(motorLeftBack, 255);
  delay(100);
}*/

void loop() {
  //Serial.println("working");
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  delay(20);
  if(distance >20){
    analogWrite(motorLeftBack, 0);
    analogWrite(motorRightBack, 0);
    analogWrite(motorLeft, 150);
    analogWrite(motorRight, 150); 
    delay (10);
    Serial.println(distance);
    Serial.println("GO");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wiu wiu wiu!"); 
    delay(10);
    lcd.setCursor(0, 1);
    lcd.print(distance); 
  }else{
    analogWrite(motorLeft, 0);
    analogWrite(motorRight, 0);
    analogWrite(motorLeftBack, 150);
    analogWrite(motorRightBack, 150);
    delay(10);
    analogWrite(motorRightBack, 0);
    analogWrite(motorLeft, 0);
    analogWrite(motorRight, 255);
    analogWrite(motorLeftBack, 255);
    delay(100);
    Serial.println(distance);
    Serial.println("REVERSE");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("To Helms Deep!");
    delay(10);
    lcd.setCursor(0, 1);
    lcd.print(distance); 
    delay(10);
  }
}
