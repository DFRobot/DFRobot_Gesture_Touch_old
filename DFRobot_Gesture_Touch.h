#ifndef DFROBOT_GESTURE_TOUCH
#define DFROBOT_GESTURE_TOUCH

#include "Arduino.h"

#ifdef __AVR__
  #include "SoftwareSerial.h"
  
  typedef SoftwareSerial    DFGT_Serial;
#else
  #include "HardwareSerial.h"

  typedef HardwareSerial    DFGT_Serial;
#endif

#define DF_OK   0
#define DF_ERR  -1

#define DFGT_SEND_HEAD    0xaa
#define DFGT_SEND_END     0x55

#define DFGT_RECV_HEAD   0xaa
#define DFGT_RECV_END    0x55

#define DFGT_CMD_INTERVAL   0x51
#define DFGT_CMD_SLEEP      0x52
#define DFGT_CMD_DISTANCE   0x54
#define DFGT_CMD_ENABLE     0x55

#define GT_FUN_RIGHT      0x01
#define GT_FUN_LEFT       0x02
#define GT_FUN_BACK       0x03
#define GT_FUN_FORWARD    0x04
#define GT_FUN_PULLUP     0x05
#define GT_FUN_PULLDOWN   0x06
#define GT_FUN_TOUCH1     0x09
#define GT_FUN_TOUCH2     0x0A
#define GT_FUN_TOUCH3     0x0B
#define GT_FUN_TOUCH4     0x0C
#define GT_FUN_TOUCH5     0x0D

#define DF_BIT_OFFSET(x)  (0x0001 << (x))

#define DFGT_FUN_RIGHT      DF_BIT_OFFSET(0)
#define DFGT_FUN_LEFT       DF_BIT_OFFSET(1)
#define DFGT_FUN_BACK       DF_BIT_OFFSET(2)
#define DFGT_FUN_FORWARD    DF_BIT_OFFSET(3)
#define DFGT_FUN_PULLUP     DF_BIT_OFFSET(4)
#define DFGT_FUN_PULLDOWN   DF_BIT_OFFSET(5)
#define DFGT_FUN_START1     0x01
#define DFGT_FUN_PART1      0x3f
#define DFGT_FUN_OFFSET1    0x00
#define DFGT_FUN_TOUCH1     DF_BIT_OFFSET(6)
#define DFGT_FUN_TOUCH2     DF_BIT_OFFSET(7)
#define DFGT_FUN_TOUCH3     DF_BIT_OFFSET(8)
#define DFGT_FUN_TOUCH4     DF_BIT_OFFSET(9)
#define DFGT_FUN_TOUCH5     DF_BIT_OFFSET(10)
#define DFGT_FUN_START2     0x09
#define DFGT_FUN_PART2      0x07ff
#define DFGT_FUN_OFFSET2    0x06
#define DFGT_FUN_ALL        0x07ff

#define DFGT_EVT_RIGHT        0x01
#define DFGT_EVT_LEFT         0x02
#define DFGT_EVT_BACK         0x03
#define DFGT_EVT_FORWARD      0x04
#define DFGT_EVT_PULLUP       0x05
#define DFGT_EVT_PULLDOWN     0x06
#define DFGT_EVT_PULLREMOVE   0x07
#define DFGT_EVT_TOUCH1       0x21
#define DFGT_EVT_TOUCH2       0x22
#define DFGT_EVT_TOUCH3       0x23
#define DFGT_EVT_TOUCH4       0x24
#define DFGT_EVT_TOUCH5       0x25

#define DFGT_SLEEP_DISABLE    0xff

typedef struct {
  uint8_t   head;
  uint8_t   cmd;
  uint8_t   value;
  uint8_t   verify;
  uint8_t   end;
} sDFGT_send_t;

typedef struct {
  uint8_t   head;
  uint8_t   data;
  uint8_t   verify;
  uint8_t   end;
} sDFGT_receive_t;

class DFRobot_Gesture_Touch
{
public:
  DFRobot_Gesture_Touch(DFGT_Serial *pSerial) { _pSerial = pSerial; }

  void    setGestureDistance(uint8_t dis);
  void    setSleep(uint8_t sec);
  void    enableFunction(uint16_t func);
  void    disableFunction(uint16_t func);

  int8_t    getAnEvent();
  
private:
  void    set(uint8_t cmd, uint8_t value);
  void    enableFunctionHelper(uint8_t start, uint16_t func);

  sDFGT_send_t      _sSend;
  sDFGT_receive_t   _sRecv;
  
  DFGT_Serial   *_pSerial;
};

#endif
