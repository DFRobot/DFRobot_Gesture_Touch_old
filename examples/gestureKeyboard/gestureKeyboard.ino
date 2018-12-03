/*
 * file gestureKeyboard.ino
 *
 * @ https://github.com/DFRobot/DFRobot_Gesture_Touch
 *
 * example for gesture keyboard on Arduino leonardo
 *
 * output key on your computer.
 * more detail for Keyboard, you can reference here:
 * https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2018-10-19
 */

#include "Keyboard.h"
#include "DFRobot_Gesture_Touch.h"

#include "SoftwareSerial.h"
SoftwareSerial    mySerial(10, 11);         // example for uno, use software serial

DFRobot_Gesture_Touch   DFGT(&mySerial);    // init sensor object, request write and read function

void setup()
{
  mySerial.begin(9600);
  Serial.begin(115200);
  Keyboard.begin();
  while(!Serial);                                         // wait until usb serial open
  Serial.println("gesture keyboard demo on leonardo");    
  DFGT.enableFunction(DFGT_FUN_ALL);
}

void pressHelper(uint8_t key)  // press and release key
{
  Keyboard.press(key);
  Keyboard.releaseAll();
}

void loop()
{
  int8_t    rslt = DFGT.getAnEvent();  // get an event that data saved in serial's buffer
  if(rslt != DF_ERR) {
    switch(rslt) {
      case DFGT_EVT_BACK: {
        Serial.println("get event back");
        pressHelper('A');
      } break;
      case DFGT_EVT_FORWARD: {
        Serial.println("get event forward");
        pressHelper('B');
      } break;
      case DFGT_EVT_RIGHT: {
        Serial.println("get event right");
        pressHelper('C');
      } break;
      case DFGT_EVT_LEFT: {
        Serial.println("get event left");
        pressHelper('D');
      } break;
      case DFGT_EVT_PULLUP: {
        Serial.println("get event pull up");
        pressHelper('E');
      } break;
      case DFGT_EVT_PULLDOWN: {
        Serial.println("get event pull down");
        pressHelper('F');
      } break;
      case DFGT_EVT_PULLREMOVE: {
        Serial.println("get event pull and remove");
        pressHelper('G');
      } break;
      case DFGT_EVT_TOUCH1: {
        Serial.println("get event touch1");
        pressHelper('H');
      } break;
      case DFGT_EVT_TOUCH2: {
        Serial.println("get event touch2");
        pressHelper('I');
      } break;
      case DFGT_EVT_TOUCH3: {
        Serial.println("get event touch3");
        pressHelper('J');
      } break;
      case DFGT_EVT_TOUCH4: {
        Serial.println("get event touch4");
        pressHelper('K');
      } break;
      case DFGT_EVT_TOUCH5: {
        Serial.println("get event touch5");
        pressHelper('L');
      } break;
    }
  }
}
