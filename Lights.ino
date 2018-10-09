void calculateLights(){
  unsigned long now = millis();
  for (int i = 0; i<(sizeof(brightness));i++){
    switch (lightsAction[i]){
      case LIGHTS_OFF:
        brightness[i] = minBrightness;
        break;
      case LIGHTS_ON:
        brightness[i] = maxBrightness;
        break;
      case LIGHTS_BRIGHTEN:
        if((now - lightsChangeTime[i]) >= lightTurnOnTime){
          lightsAction[i] = LIGHTS_ON;
          brightness[i] = maxBrightness;
        } else {
          long currentStep = now - lightsChangeTime[i];
          brightness[i] = (currentStep * (maxBrightness-minBrightness)/lightTurnOnTime) + minBrightness;
        }
        break;
      case LIGHTS_DIM:
        if((now - lightsChangeTime[i]) >= lightTurnOffTime){
          lightsAction[i] = LIGHTS_OFF;
          brightness[i] = 0;
        } else {
          long currentStep = now - lightsChangeTime[i];
          brightness[i] = maxBrightness - (currentStep * (maxBrightness-minBrightness)/lightTurnOffTime);
        }
        break;
    }
  }
}
 

void showLights(void){
  for (int i = 0; i<(sizeof(brightness));i++){
    analogWrite(lightPins[i], brightness[i]);
  }
}

void lightsOff(void){
  for (int i = 0; i<(sizeof(brightness));i++){
    brightness[i] = 0;
    analogWrite(lightPins[i], 0);
  }
}
