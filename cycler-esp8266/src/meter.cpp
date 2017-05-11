#include "Meter.h"


Meter::Meter() : _speedMA(5) {
}

void Meter::begin() {
  this->reset();
  this->_lastMillis = millis();
}

void Meter::handle() {
  if (millis() - this->_lastMillis > CHECK_INTERVAL) {
    this->_tantaneousSpeed = (this->getDistance() - this->_lastDistance) / (CHECK_INTERVAL / 1000) * 60 * 60;
    this->_speed = this->_speedMA.process(this->_tantaneousSpeed);
    this->_lastMillis = millis();
    this->_lastDistance = this->getDistance();
  }
}


void Meter::reset() {
  this->_cycles = 0;
}

void Meter::interrupt() {
  this->_cycles++;
}

float Meter::getSpeed() {
  return this->_speed;
}

float Meter::getTantaneousSpeed() {
  return this->_tantaneousSpeed;
}

float Meter::getDistance() {
  return (float)this->_cycles * 2 / 1000;
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

String Meter::getFormatedTantaneousSpeed() {
  return String(this->getTantaneousSpeed()) + " km/h";
}
