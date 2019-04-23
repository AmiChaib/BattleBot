# Project BattleBot Group IT1C

In the following you can find a description of how our program works. The function mainly used are described in more detail.

## Overview

The main file is [Final.ino](/BasicFunctions/Final/Final.ino).

The main function is 
  ```java
  void loop() {...}
  ```
it first calls
  ```java
  int getServerMessage() {...}
  ```
Which returns the processed server message as *int gameMode*. A valid *gameMode* can be between 1 and 5.

**Here a game mode overview:**

| int   | game mode description     | function          | 
| :---: | ------------------------- | ----------------- |
| 1     | Obstacle avoiding         | obstacleRace()    |
| 2     | Line following            | followLine()      |
| 3     | Waypoints                 | manual            |
| 4     | Sumo                      | manual            |
| 5     | Football                  | manual            |

- For a manually controlled *gameMode*
    ```java
    int ProcessServer(String serverMessage) {...}
    ```
  directly triggeres the motors.

- For a not manually controlled *gameMode*
    ```java
    void loop() {...}
    ```
  calles the corresponding function.


### Function obstacleRace()

The obstacleRace() function checks the distance between the bot and the next obstacle; when the distance is too small the direction to turn to is determined, if the total turning degree has been larger than 90°, the bot is turned back to its initial direction.

**Description:**
  > - Measures distance through getDistance() function.
  > - As long as the returned distance value is larger than 25 calls forward() function with a speed of 220 for 30ms, then               triggeres getDistance again.
  > - Distance value is less than 25, calls halt() and then backwards() function and determines direction through getDirection()         function. getDirection() turns the bot into chosen direction and increases the local variable *timeTurned* by the time the         bot turned into that direction.
  > - If timeTurned reaches more than 250 (close to time a 90° turn takes (for #08 275ms)) turns back 90° and resets variables,         changes index (needed for getDirection() to determine direction).


### Function followLine()

The followLine() funtion checks whether the left sensor **LS** or the right sensor **RS** detect a black line.
A local variable *int direction* is created.

**Description:**
  > - If **no black line is detected**, the forward() function is triggered with a speed of 150 for 20ms.
  > - If the **RS detects a black line** and LS does not, the turnLeft() function is triggered with a speed of 100 for 60ms and         *direction* is set to 1.
  > - If the **LS detects a black line** and RS does not, the turnRight() function is triggered with a speed of 100 for 60ms and         *direction* is set to 2.
  > - If **both sensors detect a black line** and ***direction* is 1** (it was turning left previously), the turnLeft() function         is triggered with a speed of 120 for 30ms.
  > - If **both sensors detect a black line** and ***direction* is 2** (it was turning right previously), the turnRight() function       is triggered with a speed of 120 for 30ms.
  > - If **both sensors detect a black line** and ***direction* is anything else**, the forward() function is
      triggered with a speed of 150 for 20ms.


### Basic Functions

Here you can find a short explanation for all basic funtions used in obstacleRace() and followLine(). 

  - 
  ```java
  void halt(){...}
  ```
  stops all motors, prints "Stop!" on lcd display.
  
  - 
  ```java
  void forward(int speeed, int timey){...}
  ```
  uses *halt()* then spins motors forward with input speed (parameter *speedy* - must be between 0 and 256) and for time in ms       (parameter *timey*), prints "Wiu wiu wiu!" on lcd display.
  
  
  - 
  ```java
  void backwards(int speeed, int timey){...}
  ```
  uses *halt()* then spins motors backwards with input speed (parameter *speedy* - must be between 0 and 256) and for time in ms     (parameter *timey*), prints "Beep beep beep!" on lcd display.
  
  
  - 
  ```java
  void turnRight(int speeed, int timey){...}
  ```
  uses *halt()* then spins left motor forward with input speed (parameter *speedy* - must be between 0 and 256) and right motor     backwards at full speed to turn right for time in ms (parameter *timey*), prints "To the right!" on lcd display.
  
  
  - 
  ```java
  void turnleft(int speeed, int timey){...}
  ```
  uses *halt()* then spins right motor forward with input speed (parameter *speedy* - must be between 0 and 256) and left motor     backwards at full speed to turn left for time in ms (parameter *timey*), prints "To the left!" on lcd display.
  
  
  - 
  ```java
  void right90(){...}
  ```
  uses *turnRight(255, 275)* (255 = full speed, 275ms is the time robot 8 with rubberbands took to turn 90°).
  
  - 
  ```java
  void left90(){...}
  ```
  uses *turnLeft(255, 275)* (255 = full speed, 275ms is the time robot 8 with rubberbands took to turn 90°).
  
  - 
  ```java
  void getDistance(){...}
  ```
  triggers ultrasonic sensors (transmits and receives signal) and calculates a value for distance.
  
  - 
  ```java
  void getDirection(){...}
  ```
  depending on previous direction (indicated by *int index* set in *obstacleRace()* function) turns bot into the opposite           direction and adds the time it has turned to *int timeTurned* (used in *obstacleRace()* function).



> Authors of code: Philip Blesinger, Christof du Toit, Amira Chaib

> Author of documentation: Amira Chaib
