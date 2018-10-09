void sendChar(int i){
  if (sendKeyboard){
    switch(i){
      case UP:
        Keyboard.press(KEY_UP_ARROW);
        break;
      case DOWN:
        Keyboard.press(KEY_DOWN_ARROW);
        break;
      case LEFT:
        Keyboard.press(KEY_LEFT_ARROW);
        break;
      case RIGHT:
        Keyboard.press(KEY_RIGHT_ARROW);
        break;
    }
  }
}


void releaseChar(int i){
  if (sendKeyboard){
    switch(i){
      case UP:
        Keyboard.release(KEY_UP_ARROW);
        break;
      case DOWN:
        Keyboard.release(KEY_DOWN_ARROW);
        break;
      case LEFT:
        Keyboard.release(KEY_LEFT_ARROW);
        break;
      case RIGHT:
        Keyboard.release(KEY_RIGHT_ARROW);
        break;
    }
  }
}

void performAction(int i){
  switch(i){
    case UP:
      if (minBrightness + dimmerIncrement <= maxDimmer){
        minBrightness += dimmerIncrement;
      } else {
        minBrightness = maxDimmer;
      }
      break;
    case DOWN:
      if (minBrightness - dimmerIncrement >= 0){
        minBrightness -= dimmerIncrement;
      } else {
        minBrightness = 0;
      }
      break;
    case LEFT:
      if (useLights == 1 && lightTurnOffTime == 0){
        useLights = 0;
      } else if (lightTurnOffTime - turnOffIncrement >= 0) {
        lightTurnOffTime -= turnOffIncrement;
      } else {
        lightTurnOffTime = 0;
      }
      break;
    case RIGHT:
      Serial.println(lightTurnOffTime);
      if (useLights == 0){
        useLights = 1;
      } else if (lightTurnOffTime + turnOffIncrement <= maxTurnOffTime) {
        lightTurnOffTime += turnOffIncrement;
      } else {
        lightTurnOffTime = maxTurnOffTime;
      }
      break;
  }
}
      
