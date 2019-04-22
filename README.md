# Project BattleBot Group IT1C

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

**Here an overview:**

| int   | gameMode description      | function          | 
| :---: | ------------------------- | ----------------- |
| 1     | Obstacle avoiding         | obstacleRace()    |
| 2     | Line following            | followLine()      |
| 3     | Waypoints                 | manual            |
| 4     | Sumo                      | manual            |
| 5     | Football                  | manual            |


## Function obstacleRace()


## Function followLine()

The followLine() funtion checks whether the left sensor **LS** or the right sensor **RS** detect a black line.
A local variable *int direction* is created.
  > - As long as no black line is detected, the forward() function is triggered with a speed of 150 for 20ms.
  > - If the **RS detects a black line** and LS does not, the turnLeft() function is triggered with a speed of 100 for 60ms and *direction* is set to 1.
  > - If the **LS detects a black line** and RS does not, the turnRight() function is triggered with a speed of 100 for 60ms and *direction* is set to 2.
  > - If both sensors detect a black line and *direction* is 1 (it was turning left previously), the turnLeft() function is             triggered with a speed of 120 for 30ms.
  > - If both sensors detect a black line and *direction* is 2 (it was turning right previously), the turnRight() function is 
      triggered with a speed of 120 for 30ms.
  > - If both sensors detect a black line and *direction* is anything else, the forward() function is
      triggered with a speed of 150 for 20ms.
