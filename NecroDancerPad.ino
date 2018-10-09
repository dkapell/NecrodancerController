/* 

Necrodancer controller 
Written By Dave Kapell (@dkapell)

This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
http://creativecommons.org/licenses/by-sa/4.0

*/

#include <EEPROM.h>
#include "pad.h"

const int keyboardSwitchPin = 12;
//unused 0,1,10,11,13, A0-5



byte buttonPins[] = {2,4,7,8};
byte lightPins[] = {3,5,6,9};

byte buttonStates[4];
byte lastButtonStates[4];
long lastDebounceTimes[4];
long debounceDelay = 30;

byte maxBrightness=255;
byte minBrightness=8;
byte brightness[] = {0,0,0,0};

const byte LIGHTS_OFF = 0;
const byte LIGHTS_BRIGHTEN = 1;
const byte LIGHTS_ON = 2;
const byte LIGHTS_DIM = 3;

long lightsChangeTime[4];
long lightsAction[] = {LIGHTS_OFF, LIGHTS_OFF, LIGHTS_OFF, LIGHTS_OFF};

long turnOffIncrement = 50;
byte dimmerIncrement = 4;

long maxTurnOffTime = 1000;
long maxDimmer = 64;

long lightTurnOnTime = 0;
long lightTurnOffTime = 200;

byte useLights = 1;
boolean sendKeyboard = false;

void setup(){
  for (int i = 0; i<(sizeof(buttonPins));i++){
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
    buttonStates[i] = HIGH;
    lastButtonStates[i] = HIGH;
    lastDebounceTimes[i] = 0;
    pinMode(lightPins[i], OUTPUT);
    analogWrite(lightPins[i], 0);
    
  }
  
  pinMode(keyboardSwitchPin, INPUT);
  digitalWrite(keyboardSwitchPin, HIGH);
  
  loadSettings();
  
  Keyboard.begin();
}


void loop(){
  if (digitalRead(keyboardSwitchPin) == LOW){
    if (sendKeyboard == false){
      saveSettings();
    }
    sendKeyboard = true;
  } else {
    sendKeyboard = false;
  }
  
  for (int i = 0; i<(sizeof(buttonPins));i++){
    byte reading = digitalRead(buttonPins[i]);
    if (reading != lastButtonStates[i]){
      lastDebounceTimes[i] = millis();
    }
    if ((millis() - lastDebounceTimes[i]) > debounceDelay){
      if (reading != buttonStates[i]){
        buttonStates[i] = reading;
        
        if (reading == LOW) { // Button pressed
          if(sendKeyboard){
            sendChar(i);
          } else {
            performAction(i);
          }
          if (useLights){
            lightsAction[i] = LIGHTS_BRIGHTEN;
            lightsChangeTime[i] = millis();
          }
          
        } else {   // button released
          if(sendKeyboard){ 
            releaseChar(i);
          }
          if(useLights){
            lightsAction[i] = LIGHTS_DIM;
            lightsChangeTime[i] = millis();
          }
          
        }
      }
    }
    
    lastButtonStates[i] = reading;
  }
  
  calculateLights();
  showLights();
}


  

  

  
