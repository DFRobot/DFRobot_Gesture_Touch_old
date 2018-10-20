#include "DFRobot_Gesture_Touch.h"

void DFRobot_Gesture_Touch::set(uint8_t cmd, uint8_t value)
{
  _sSend.head = DFGT_SEND_HEAD;
  _sSend.end = DFGT_SEND_END;
  _sSend.cmd = cmd;
  _sSend.value = value;
  _sSend.verify = cmd ^ value;
  uint8_t   *pData = (uint8_t*) &_sSend;
  for(uint8_t i = 0; i < sizeof(_sSend); i ++)
    _pSerial->write(pData[i]);
  delay(2);
}

void DFRobot_Gesture_Touch::setGestureInterval(uint16_t t)
{
  if(t > 2550)
    return;
  set(DFGT_CMD_INTERVAL, t / 10);
}

void DFRobot_Gesture_Touch::setGestureDistance(uint8_t dis)
{
  if(dis > 30)
    return;
  set(DFGT_CMD_DISTANCE, 0x20 + (0xfe - 0x20) / 30 * dis);
}

void DFRobot_Gesture_Touch::setSleep(uint8_t sec)
{
  if(sec == 1)
    return;
  set(DFGT_CMD_SLEEP, sec);
}

void DFRobot_Gesture_Touch::enableFunction(uint8_t func)
{
  if(func == DFGT_FUN_ALL) {
    for(uint8_t i = 0x11; i < 0x17; i ++)
      set(DFGT_CMD_ENABLE, i);
    for(uint8_t i = 0x19; i < 0x1e; i ++)
      set(DFGT_CMD_ENABLE, i);
  } else
    set(DFGT_CMD_ENABLE, func | 0x10);
}

void DFRobot_Gesture_Touch::disableFunction(uint8_t func)
{
  if(func == DFGT_FUN_ALL) {
    for(uint8_t i = 0x01; i < 0x07; i ++)
      set(DFGT_CMD_ENABLE, i);
    for(uint8_t i = 0x09; i < 0x0e; i ++)
      set(DFGT_CMD_ENABLE, i);
  } else
    set(DFGT_CMD_ENABLE, func);
}

int8_t DFRobot_Gesture_Touch::getAnEvent()
{
  uint8_t   i = 0;
  uint8_t   *pRecv = (uint8_t*) &_sRecv;
  while(_pSerial->available()) {
    if(_pSerial->peek() == DFGT_RECV_HEAD) {
      if(_pSerial->available() >= sizeof(_sRecv)) {
        for(; i < sizeof(_sRecv); i ++)
          pRecv[i] = _pSerial->read();
        if((_sRecv.head == DFGT_RECV_HEAD) && (_sRecv.end == DFGT_RECV_END) && (_sRecv.data == (0xff - _sRecv.verify)))
          return _sRecv.data;
        return DF_ERR;
      } else
        return DF_ERR;
    } else
      _pSerial->read();
  }
  return DF_ERR;
}
