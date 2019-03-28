#define speedy 10
int angle 0
int timeDriven 0
int currentPoint 0
#define coords 005003

void setup() {
  /*
  int x = millis();
  int y = millis() - x;
  */
  distanceX = coords % 1000 ;
  timeToDriveX = distanceX / speedy;
  // someForwardFunction (some speed, timeToDriveX);
  // some90TurnFunction ();
  distanceY = (coords - distanceX)/1000;
  timeToDriveY = distanceY / speedy;
  //some ForwardFunction (some speed, timeToDriveY);
  //return current coord or save it or some shit
  //if you input another coordinate newcoord - old coord is the path you need to drive
  // make if statement for turnaround function when path contains negative value 
}

void loop() {
  // put your main code here, to run repeatedly:

}
