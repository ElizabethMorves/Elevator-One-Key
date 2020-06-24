#include <Arduino.h>
#include "travel.h"
#include "rtos.h"

//KEY         2             //One key
//MAINRELAY   4             //main relay
//RELAYUP     5             //relay move up
//RELAYDOWN   6             //relay move down
//SWITHTOP    8             //switch up
//SWITHBOTTOM 9             //switch bottom

#define MAINRELAYTIMER 300  //timeout all off in seconds
#define TIMEALLOWMOVE 1     //timeout press key in seconds/2

ElevatorState elevator;

void ElevatorState::begin(){
  _up = false;
  _down = true;
  _stop = true;

    DDRD |= B01110000;
    PORTD |= B01110000;
    DDRB |= B00000000;
    PORTB |= B00000011;
}
bool ElevatorState::sleep(uint16_t &_timer){
  if(_timer > 0){
    --_timer;
    return false;
  }else{
    _timer = 0;
    return true;
  }
  return true;
}

void ElevatorState::uslip(){
  _timer = MAINRELAYTIMER * 2;
}

bool ElevatorState::GeneralMove(){
  if(_stop && _down && !(PORTD & B00010000)){
    this->down();
    return true;
  }
  if(_stop && _up && !(PORTD & B00010000)){
    this->up();
    return true;
  }
  if(!_stop && !(PORTD & B00010000)){
    this->alarmStop();
    return true;
  }
  return false;
}

bool ElevatorState::limit(){
  if(!(PINB & B00000001) || !(PINB & B00000010)) {
    this->stop();
    return true;
  }
  return false;
}

bool ElevatorState::moveAllow(){
  if(((_timer + TIMEALLOWMOVE) < MAINRELAYTIMER * 2) && (_timer != 0) ){
    return true;
  }
  return false;
}

void ElevatorState::mainRelay(){
  if ( this->sleep(_timer)){
    if(!(PORTD & B00010000)){
      this->alarmStop();
      PORTD ^= B00010000;
    }
  }else{
    if(PORTD & B00010000){
      PORTD ^= B00010000;
    }
  }
}

void ElevatorState::up(){
  PORTD ^= B00100000;
  _up = false; _down = true; _stop = false;
}

void ElevatorState::down(){
  PORTD ^= B01000000;
  _up = true; _down = false; _stop = false;
}

void ElevatorState::stop(){
  if(!(PORTD & B00010000)){
    if(!(PORTD & B00100000) && !(PINB & B00000001)) { PORTD ^= B00100000; _stop = true;}
    if(!(PORTD & B01000000) && !(PINB & B00000010)) { PORTD ^= B01000000; _stop = true;}
  }
}
void ElevatorState::alarmStop(){
  if(!(PORTD & B00010000)){
    if(!(PORTD & B00100000)) { PORTD ^= B00100000; _stop = true;}
    if(!(PORTD & B01000000)) { PORTD ^= B01000000; _stop = true;}
  }
}
