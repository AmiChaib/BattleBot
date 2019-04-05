/* ----------------------------------------------------------- LIBRARIES ----------------------------------------------------------- */
#include <SoftwareSerial.h>
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

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
  /* ---------- //lcd ----------  */
  //lcd.begin(16, 2);
  //lcd.backlight();
  //lcd.setCursor(0, 0);
  //lcd.print("Awaiting orders!");
  //delay(1000);
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
  //lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print("Stop!");
  //lcd.setCursor(0, 1);
  //lcd.print("Awaiting orders!");
}

/* Just to clarify: 
 * 'speed' and 'time' seem to have some other use and so in the following I chose speeed and timey instead.
 * So we should not get any problems with that. #safetyFirst :)
 */

/* ----- moving forward -----   */
void forward(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("Wiu wiu wiu!"); 
    analogWrite(motorForwardLeft, speeed);
    analogWrite(motorForwardRight, speeed);
    delay(timey); 
  } 
}

/* ----- moving backwards ----- */
void backwards(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("Beep beep beep!");
    analogWrite(motorBackwardsLeft, speeed);
    analogWrite(motorBackwardsRight, speeed);
    delay(timey);
  } 
}

/* -- turning right on spot --  */
void turnRight(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //I wish we had LEDs on both sides of the arduino, like the indicators on a car :3
    //lcd.print("To the right!"); 
    analogWrite(motorForwardLeft, speeed);
    analogWrite(motorBackwardsRight, speeed);
    delay(timey);
  } 
}

/* --- turning left on spot --- */
void turnLeft(int speeed, int timey){
  if((speeed > 0) && (speeed < 256)){
    halt();
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("To the left!");
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
/* ---- getting server msg ---- */
String GetServerMessage() {
  String serverMessage = ""; // Creates variable for serverMessage
  while (serial.available() > 0) { // Reads while the server is sending stuff
    serverMessage.concat((char)serial.read()); // Gets a character from the server
  }
  if(serverMessage != ""){ // Checks if there was a serverMessage received
    if (serverMessage.length() == 8){ // Checks if the serverMessage was 8 characters long
      if(serverMessage == "00000000") // Checks if it's "00000000", it came to a stop
        serial.write("stop"); // Sends "stop" signal to server
      else
       serial.write("move"); // Sends "move" signal to the server
    }
  }
  return serverMessage; // Returns the serverMessage
}
/* -- processing server msg --  */
void ProcessServer(String serverMessage) {
  // Parsing logic: example: 12512500
  //   125           125           0             0
  // FrontLeft | FrontRight | ReverseLeft | ReverseRight
  
  int FL = serverMessage.substring(0, 3).toInt();
  int FR = serverMessage.substring(3, 6).toInt();
  int RL = serverMessage.substring(6, 7).toInt();
  int RR = serverMessage.substring(7).toInt();
  analogWrite(m_FL, FL);
  analogWrite(m_FR, FR);
  if(RL != 0)
    digitalWrite(m_RL, HIGH);
  else
    digitalWrite(m_RL, LOW);
  if(RR != 0)
    digitalWrite(m_RR, HIGH);
  else
    digitalWrite(m_RR, LOW);
}
/* ------ manual control ------ */
void manual(){
  ProcessServer(GetServerMessage());
  delay(25);
}
/* -------- waypoints --------  */
void waypoints(){
  halt(); //replace with waypoints method
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

/* ---------------------- getting game modes ---------------------- */
/*  get game mode from server   */
String getGameMode() {
  // game modes:
  // 0    None
  // 1    Obstacle race
  // 2    Follow the line
  // 3    Waypoints
  // 4    Sumo
  // 5    Football
  if(serial.available() == 1) {
    String serverMessage = ""; // Creates variable for serverMessage
    serverMessage.concat((char)serial.read()); // Reads the character
    if(serverMessage.length() == 1) { // Checks if message is only one character
      return serverMessage; // returns serverMessage
    }
  }
  return "";
}

/* --------------------------------------------------------- EXECUTING LOOP -------------------------------------------------------- */
void loop(){
  boolean manualControl = false;
  if(GetServerMessage() != ""){
    ProcessServer(GetServerMessage());
    Serial.println(GetServerMessage());
  }
  /* -- determining game mode --   */
  String gameMode = getGameMode();
  Serial.println(gameMode);
  if(gameMode == "1"){
    obstacleRace();
  }
  else if(gameMode == "2"){
    followLine();
  }
  else if(gameMode == "3"){
    waypoints();
  }
  else if((gameMode == "4") || (gameMode == "5")){
    manualControl = true;
    if(manualControl){
      manual();
      return;
    }
  }
  else{
    halt();
  } 
}
