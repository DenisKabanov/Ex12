// Copyright 13.04.21 DenisKabanov

#include <iostream>
#include <thread>
#include <chrono>
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
  std::string message;
  if (isDoorOpened() == true) {
    message = "close the door!";
  } else {
    message = "the door is closed!";
  }
  throw(message);
}

void Timer::sleep(int delayTime) {
  std::this_thread::sleep_for(std::chrono::seconds(delayTime));
}

void Timer::tregister(int delayTime, TimerClient* adapter) {
  sleep(delayTime);
  adapter->Timeout();
}
