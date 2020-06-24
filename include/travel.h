#ifndef TRAVEL_H
#define TRAVEL_H
#include <Arduino.h>

class ElevatorState{
public:
  void begin();
  bool sleep(uint16_t &_timer);
  void uslip();
  void mainRelay();
  bool moveAllow();
  bool GeneralMove();
  bool limit();

private:
  void up();
  void down();
  void stop();
  void alarmStop();
  bool _up;
  bool _down;
  bool _stop;
  uint16_t _timer;
};

extern ElevatorState elevator;
#endif
