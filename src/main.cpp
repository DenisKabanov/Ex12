// Copyright 13.04.21 DenisKabanov

#include <iostream>
#include "TimedDoor.h"

int main() {
  TimedDoor tDoor(5);
  tDoor.lock();
  tDoor.unlock();
  return 0;
}