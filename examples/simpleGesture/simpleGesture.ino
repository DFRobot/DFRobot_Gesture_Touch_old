/*
 * file simpleGesture.ino
 *
 * @ https://github.com/DFRobot/DFRobot_Gesture_Touch
 *
 * example for DFRobot Gesture&Touch sensor
 *
 * sensor event will print on your serial monitor
 *
 * for esp32, rx_pin = D5, tx_pin = D6
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2018-10-19
 */
 
#include "DFRobot_Gesture_Touch.h"

#ifdef __AVR__
  #include "SoftwareSerial.h"
  SoftwareSerial    mySerial(10, 11);         // example for uno, use software serial
#elif defined ESP_PLATFORM
  #include "HardwareSerial.h"
  HardwareSerial    mySerial(1);
#endif

DFRobot_Gesture_Touch   DFGT(&mySerial);    // init sensor object, request write and read function

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
  delay(500);
  while(mySerial.available())  // flush serial buffer
    mySerial.read();
  Serial.println("gesture&touch sensor test");

  DFGT.setGestureDistance(20);             // suggest default value
  DFGT.enableFunction(DFGT_FUN_ALL);       // enable all functions
  // DFGT.disableFunction(DFGT_FUN_RIGHT | DFGT_FUN_LEFT);    // disable function test
  delay(20);
  // DFGT.enableFunction(DFGT_FUN_RIGHT | DFGT_FUN_LEFT);     // enable function test
  DFGT.setSleep(4);                        // set auto sleep time out, in sleep mode, something  approach will weak it up
}

void loop()
{
  int8_t    rslt = DFGT.getAnEvent();  // get an event that data saved in serial buffer
  if(rslt != DF_ERR) {
    // DFGT.setSleep(DFGT_SLEEP_DISABLE);  // disable auto sleep
    switch(rslt) {
      case DFGT_EVT_BACK: {
        Serial.println("get event back");
      } break;
      case DFGT_EVT_FORWARD: {
        Serial.println("get event forward");
      } break;
      case DFGT_EVT_RIGHT: {
        Serial.println("get event right");
      } break;
      case DFGT_EVT_LEFT: {
        Serial.println("get event left");
      } break;
      case DFGT_EVT_PULLUP: {
        Serial.println("get event pull up");
      } break;
      case DFGT_EVT_PULLDOWN: {
        Serial.println("get event pull down");
      } break;
      case DFGT_EVT_PULLREMOVE: {
        Serial.println("get event pull and remove");
      } break;
      case DFGT_EVT_TOUCH1: {
        Serial.println("get event touch1");
      } break;
      case DFGT_EVT_TOUCH2: {
        Serial.println("get event touch2");
      } break;
      case DFGT_EVT_TOUCH3: {
        Serial.println("get event touch3");
      } break;
      case DFGT_EVT_TOUCH4: {
        Serial.println("get event touch4");
      } break;
      case DFGT_EVT_TOUCH5: {
        Serial.println("get event touch5");
      } break;
    }
  }
}
