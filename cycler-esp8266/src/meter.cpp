#include "meter.h"


void Meter::begin() {
  this->reset();
}

void Meter::reset() {
  this->_cycles = 0;
}

void Meter::handle() {
}

void Meter::interrupt() {
  this->_cycles++;
}

double Meter::getSpeed() {
  return 0;
}

double Meter::getDistance() {
  return this->_cycles * 2 / 1000;
}

String Meter::getFormatedDistance() {
  return String(this->getDistance()) + " km";
}

String Meter::getFormatedTime() {
  return "00:00";
}

String Meter::getFormatedSpeed() {
  return String(this->getSpeed()) + " km/h";
}
