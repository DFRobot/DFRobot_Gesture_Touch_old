# -*- coding:utf-8 -*-

import sys

from DFRobot_Gesture_Touch import Gesture_Touch

if sys.platform.find("linux") >= 0:  # raspberry
  GT = Gesture_Touch()
elif sys.platform == "esp32":  # esp32
  GT = Gesture_Touch(txPin = 10, rxPin = 9)

print("Gesture&Touch sensor test")

#GT.setGestureDistance(20)           # suggest default value
#GT.enableFunction(GT.FUN_ALL)       # enable all functions
#GT.disableFunction(GT.FUN_RIGHT | GT.FUN_LEFT)    # disable function test
#GT.enableFunction(GT.FUN_RIGHT | GT.FUN_LEFT)     # enable function test
#GT.setSleep(10)                     # set auto sleep time out

while True:
  rslt = GT.getAnEvent()
  if rslt != GT.ERR:
    if rslt == GT.EVT_BACK:
      print("get event back")
    elif rslt == GT.EVT_FORWARD:
      print("get event forward")
    elif rslt == GT.EVT_LEFT:
      print("get event left")
    elif rslt == GT.EVT_PULLDOWN:
      print("get event pull down")
    elif rslt == GT.EVT_PULLREMOVE:
      print("get event pull remove")
    elif rslt == GT.EVT_PULLUP:
      print("get event pull up")
    elif rslt == GT.EVT_RIGHT:
      print("get event right")
    elif rslt == GT.EVT_TOUCH1:
      print("get event touch1")
    elif rslt == GT.EVT_TOUCH2:
      print("get event touch2")
    elif rslt == GT.EVT_TOUCH3:
      print("get event touch3")
    elif rslt == GT.EVT_TOUCH4:
      print("get event touch4")
    elif rslt == GT.EVT_TOUCH5:
      print("get event touch5")
  GT.sleep(0.01)

