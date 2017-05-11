#ifndef meter_h
#define meter_h

#include <Arduino.h>
#include <MovingAverageFilter.h>


const int CHECK_INTERVAL = 3000;


class Meter {
public:
  Meter();
  void begin();
  void handle();
  void interrupt();
  void reset();
  float getDistance();
  float getSpeed();
  float getTantaneousSpeed();
  String getFormatedDistance();
  String getFormatedSpeed();
  String getFormatedTantaneousSpeed();
  String getFormatedTime();

private:
  int _cycles = 0;
  float _tantaneousSpeed = 0;
  float _speed = 0;
  int _lastMillis = 0;
  float _lastDistance = 0;
  MovingAverageFilter _speedMA;
};

#endif
