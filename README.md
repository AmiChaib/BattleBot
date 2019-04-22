# Project BattleBot Group IT1C
 
```java
int gameMode = 0;
void loop(){
  /* -- determining game mode --   */
  int temp = GetServerMessage();
  if(temp != -1){
    gameMode = temp;
  }
  /* ---- running game mode ----   */
  if(gameMode == 3 || gameMode == 4 || gameMode == 5){
    delay(50);
    return;
  }
  else if(gameMode == 1){
    obstacleRace();
  }
  else if(gameMode == 2){
    followLine();
  }
  else{
    halt();
  }
}
```
