#ifndef meter_h
#define meter_h

#include <Arduino.h>
#include <list>
#include <MovingAverageFilter.h>

using namespace std;


const int CHECK_INTERVAL = 2000;
const int RECORD_INTERVAL = 5000;
const int MAX_RECORD_COUNT = 60 * 60 / 15;


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
  list<float> getSpeedRecords();

private:
  int _cycles = 0;
  float _tantaneousSpeed = 0;
  float _speed = 0;
  int _lastCheckTime = 0;
  float _lastDistance = 0;

  MovingAverageFilter _speedMA;

  int _lastRecordTime = 0;
  list<float> _speedRecords;
};

#endif
