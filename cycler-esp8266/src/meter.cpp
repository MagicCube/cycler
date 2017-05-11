#include "Meter.h"


Meter::Meter() : _speedMA(5) {

}

void Meter::begin() {
  this->reset();
  this->_lastCheckTime = millis();
}

void Meter::handle() {
  if (millis() - this->_lastCheckTime > CHECK_INTERVAL) {
    this->_tantaneousSpeed = (this->getDistance() - this->_lastDistance) / (CHECK_INTERVAL / 1000) * 60 * 60;
    this->_speed = this->_speedMA.process(this->_tantaneousSpeed);
    this->_lastDistance = this->getDistance();
    this->_lastCheckTime = millis();
  }
  if (millis() - this->_lastRecordTime > RECORD_INTERVAL) {
    this->_speedRecords.push_back(this->_speed);
    while (this->_speedRecords.size() > MAX_RECORD_COUNT) {
      this->_speedRecords.pop_front();
    }
    this->_lastRecordTime = millis();
  }
}


void Meter::reset() {
  this->_cycles = 0;
  this->_lastCheckTime = 0;
  this->_lastDistance = 0;
  this->_lastRecordTime = 0;
  this->_speed = 0;
  this->_speedRecords.clear();
  this->_tantaneousSpeed = 0;
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

list<float> Meter::getSpeedRecords() {
  return this->_speedRecords;
}
