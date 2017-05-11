#include "StopWatch.h"


void StopWatch::start() {
  if (this->getState() != StopWatch::RUNNING) {
    this->_startTime = millis();
    this->_state = RUNNING;
  }
}

void StopWatch::pause() {
  if (this->getState() == StopWatch::RUNNING) {
    this->_accElapsed = this->getElapsed();
    this->_startTime = 0;
    this->_state = PAUSED;
  }
}

bool StopWatch::isRunning() {
  return this->getState() == StopWatch::RUNNING;
}

enum StopWatch::State StopWatch::getState() {
  return this->_state;
}

void StopWatch::reset() {
  this->_accElapsed = 0;
  this->_startTime = 0;
  this->_state = StopWatch::STOPPED;
}

int StopWatch::getElapsed() {
  return this->_accElapsed + (this->_startTime == 0 ? 0 : (millis() - this->_startTime));
}

String StopWatch::getFormatedElapsed() {
  int seconds = this->getElapsed() / 1000;
  return formatDigit2(seconds / 60) + ":" + formatDigit2(seconds % 60);
}


String formatDigit2(int num) {
  if (num < 10) {
    return "0" + String(num);
  } else {
    return String(num);
  }
}
