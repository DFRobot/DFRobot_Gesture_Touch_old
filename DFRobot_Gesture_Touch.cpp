#include "DFRobot_Gesture_Touch.h"

void DFRobot_Gesture_Touch::set(uint8_t cmd, uint8_t value)
{
  _sSend.head = DFGT_SEND_HEAD;
  _sSend.end = DFGT_SEND_END;
  _sSend.cmd = cmd;
  _sSend.value = value;
  _sSend.verify = cmd ^ value;
  uint8_t   *pData = (uint8_t*) &_sSend;
  for(uint8_t i = 0; i < sizeof(_sSend); i ++) {
    _pSerial->write(pData[i]);
    delay(2);
  }
  delay(15);
}

void DFRobot_Gesture_Touch::enableFunctionHelper(uint8_t start, uint16_t func)
{
  while(func) {
    if(func & 0x01)
      set(DFGT_CMD_ENABLE, start);
    start += 1;
    func >>= 1;
  }
}

void DFRobot_Gesture_Touch::setGestureDistance(uint8_t dis)
{
  if(dis > 30)
    return;
  if(dis == 30)
    dis -= 2;
  set(DFGT_CMD_DISTANCE, 0xff);
  set(DFGT_CMD_DISTANCE, 0x20 + (0xfe - 0x20) / 30 * dis);
}

void DFRobot_Gesture_Touch::setSleep(uint8_t sec)
{
  if(sec == 1)
    return;
  set(DFGT_CMD_SLEEP, 1);
  set(DFGT_CMD_SLEEP, sec);
}

void DFRobot_Gesture_Touch::enableFunction(uint16_t func)
{
  enableFunctionHelper(DFGT_FUN_START1 | 0x10, (func & DFGT_FUN_PART1) >> DFGT_FUN_OFFSET1);
  enableFunctionHelper(DFGT_FUN_START2 | 0x10, (func & DFGT_FUN_PART2) >> DFGT_FUN_OFFSET2);
}

void DFRobot_Gesture_Touch::disableFunction(uint16_t func)
{
  enableFunctionHelper(DFGT_FUN_START1, (func & DFGT_FUN_PART1) >> DFGT_FUN_OFFSET1);
  enableFunctionHelper(DFGT_FUN_START2, (func & DFGT_FUN_PART2) >> DFGT_FUN_OFFSET2);
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
