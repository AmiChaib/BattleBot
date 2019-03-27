/*-------definning Inputs------*/ 
#define LS  10    // left sensor 
#define RS  11    // right sensor 
 
 
/*-------definning Outputs------*/ 
#define motorLeft 3   // left motor 
#define motorLeftBack 2    // left motor 
#define motorRight 9    // right motor 
#define motorRightBack 4     // right motor 
 
void setup() 
{ 
  pinMode(LS, INPUT); 
  pinMode(RS, INPUT); 
  pinMode(motorLeft, OUTPUT); 
  pinMode(motorLeftBack, OUTPUT); 
  pinMode(motorRight, OUTPUT); 
  pinMode(motorRightBack, OUTPUT); 
 
} 
 
void loop(){ 
if((digitalRead(LS)==LOW) && (digitalRead(RS)==LOW))    // Condition_1 stop 
{     
    forward(100, 50); 
  } 
   
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==HIGH))  //CONDITION-2 FORWRD 
  { 
      halt(); 
    } 
  if((digitalRead(LS)==LOW) && (digitalRead(RS)==HIGH))  // RIGHT 
  { 
    turnLeft(100, 50); 
  } 
  if((digitalRead(LS)==HIGH) && (digitalRead(RS)==LOW)) 
  { 
    turnRight(100, 50); 
  } 
} 
 
 
 
 
 
//moves forward 
void forward(int speeed, int timey){ 
  if(speeed > 0 && speeed < 256){ 
    halt(); 
    analogWrite(motorLeft, speeed); 
    analogWrite(motorRight, speeed); 
    delay(timey);  
  }  
} 
 
//moves backwards 
void backwards(int speeed, int timey){ 
  if(speeed > 0 && speeed < 256){ 
    halt(); 
    analogWrite(motorLeftBack, speeed); 
    analogWrite(motorRightBack, speeed); 
    delay(timey); 
  }  
} 
 
//turns right on spot 
void turnRight(int speeed, int timey){ 
  if(speeed > 0 && speeed < 256){ 
    halt(); 
    analogWrite(motorLeft, speeed); 
    analogWrite(motorRightBack, speeed*1.5); 
    delay(timey); 
  }  
} 
 
//turns left on spot 
void turnLeft(int speeed, int timey){ 
  if(speeed > 0 && speeed < 256){ 
    halt(); 
    analogWrite(motorRight, speeed); 
    analogWrite(motorLeftBack, speeed*1.5); 
    delay(timey); 
  }  
} 
void halt(){ 
  analogWrite(motorLeftBack, 0); 
  analogWrite(motorRightBack, 0); 
  analogWrite(motorLeft, 0); 
  analogWrite(motorRight, 0); 
   
} 
