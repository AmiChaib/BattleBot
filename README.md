# Project BattleBot Group IT1C

## Overview

The main file is [Final.ino](/BasicFunctions/Final/Final.ino).

The main function is 
  ```java
  void loop(){}
  ```
it first calls
  ```java
  int getServerMessage(){}
  ```
Which returns the processed server message as *int gameMode*. 
A valid *gameMode* can be between 1 and 5.

- For a manually controlled *gameMode*
    ```java
    int ProcessServer(String serverMessage) {}
    ```
  directly triggeres the motors.

- For a not manually controlled *gameMode*
    ```java
    void loop(){}
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

