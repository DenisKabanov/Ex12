// Copyright 13.04.21 DenisKabanov

#include <iostream>
#include "windows.h"
#include "TimedDoor.h"

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& tDoor) : doorTA(tDoor) {}

void DoorTimerAdapter::Timeout() {
  doorTA.DoorTimeOut();
}

TimedDoor::TimedDoor(int delayTime) {
  this->adapter = new DoorTimerAdapter(*this);
  this->iTimeout = delayTime;
  this->opened = false;
}

bool TimedDoor::isDoorOpened() {
    return this->opened;
}

void TimedDoor::unlock() {
  this->opened = true;
  Timer time;
  time.tregister(this->iTimeout, this->adapter);
}

void TimedDoor::lock() {
  this->opened = false;
}

void TimedDoor::DoorTimeOut() {
    throwState();
}

void TimedDoor::throwState() {
  if (isDoorOpened() == true) {
    throw("close the door!");
  } else {
    throw("the door is closed!");
  }
}

void Timer::sleep(int delayTime) {
  Sleep(delayTime * 1000);
}

void Timer::tregister(int delayTime, TimerClient* adapter) {
  sleep(delayTime);
  adapter->Timeout();
}