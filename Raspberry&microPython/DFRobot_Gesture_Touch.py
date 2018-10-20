# -*- coding:utf-8 -*-

import sys
import time

def doNothing(*argvs, **kargvs):
  return

class Gesture_Touch:

  OK = 0
  ERR = -1

  SEND_HEAD = 0xaa
  SEND_END = 0x55

  RECV_HEAD = 0xaa
  RECV_END = 0x55

  CMD_INTERVAL = 0x51
  CMD_SLEEP = 0x52
  CMD_DISTANCE = 0x54
  CMD_ENABLE = 0x55

  FUN_RIGHT = 0x01
  FUN_LEFT = 0x02
  FUN_BACK = 0x03
  FUN_FORWARD = 0x04
  FUN_PULLUP = 0x05
  FUN_PULLDOWN = 0x06
  FUN_TOUCH1 = 0x09
  FUN_TOUCH2 = 0x0A
  FUN_TOUCH3 = 0x0B
  FUN_TOUCH4 = 0x0C
  FUN_TOUCH5 = 0x0D
  FUN_ALL = 0xff

  EVT_RIGHT = 0x01
  EVT_LEFT = 0x02
  EVT_BACK = 0x03
  EVT_FORWARD = 0x04
  EVT_PULLUP = 0x05
  EVT_PULLDOWN = 0x06
  EVT_PULLREMOVE = 0x07
  EVT_TOUCH1 = 0x21
  EVT_TOUCH2 = 0x22
  EVT_TOUCH3 = 0x23
  EVT_TOUCH4 = 0x24
  EVT_TOUCH5 = 0x25

  def __init__(self, txPin = None, rxPin = None):
    self._ser = None
    self._serWrite = lambda x : x
    self._serRead = doNothing
    self._serAvailable = doNothing
    self.sleep = doNothing
    self._recvBuf = bytearray([])
    if sys.platform.find("linux") >= 0:
      import serial
      self._ser = serial.Serial("/dev/ttyAMA0", 9600)
      self._serAvailable = self._ser.inWaiting
      self._serWrite = self._ser.write
      self._serRead = self._ser.read
      self.sleep = lambda t : time.sleep(t)
      self._ser.flushInput()
    elif sys.platform == "esp32":
      import machine
      import os
      self._os = os
      self._ser = machine.UART(1, baudrate = 9600, rx = rxPin, tx = txPin)
      self._serAvailable = self._ser.any
      self._serWrite = self._ser.write
      self._serRead = self._ser.read
      self.sleep = lambda t : time.sleep(t)
    else:
      print("unsupport platform")
      exit()

  def _setCmd(self, cmd, value):
    self._serWrite(bytearray([self.SEND_HEAD, cmd, value & 0xff, (cmd ^ value) & 0xff, self.SEND_END]))
    self.sleep(0.002)

  def setGestureInterval(self, t):
    if t > 2550:
      return
    self._setCmd(self.CMD_INTERVAL, t // 10)

  def setGestureDistance(self, dis):
    if dis > 30:
      return
    self._setCmd(self.CMD_DISTANCE, 0x20 + (0xfe - 0x20) // 30 * dis)

  def setSleep(self, sec):
    if sec == 1 or sec > 255:
      return
    self._setCmd(self.CMD_SLEEP, sec)

  def enableFunction(self, func):
    if func == self.FUN_ALL:
      for i in range(0x11, 0x17):
        self._setCmd(self.CMD_ENABLE, i)
      for i in range(0x19, 0x1e):
        self._setCmd(self.CMD_ENABLE, i)
    else:
      self._setCmd(self.CMD_ENABLE, func)
  
  def disableFunction(self, func):
    if func == self.FUN_ALL:
      for i in range(0x01, 0x07):
        self._setCmd(self.CMD_ENABLE, i)
      for i in range(0x09, 0x0e):
        self._setCmd(self.CMD_ENABLE, i)
    else:
      self._setCmd(self.CMD_ENABLE, func | 0x10)
  
  def getAnEvent(self):
    rslt = self.ERR
    if self._serAvailable():
      self._recvBuf += self._serRead(self._serAvailable())
      bufLen = len(self._recvBuf)
      while self._recvBuf[0] != 0xaa and bufLen > 0:
        self._recvBuf = self._recvBuf[1 : bufLen]
        bufLen -= 1
      if bufLen >= 4:
        if self._recvBuf[0] == self.RECV_HEAD and self._recvBuf[3] == self.RECV_END and self._recvBuf[1] == (0xff - self._recvBuf[2]):
          rslt = self._recvBuf[1]
        self._recvBuf = self._recvBuf[4 : bufLen]
    return rslt

