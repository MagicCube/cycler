#ifndef meter_h
#define meter_h

#include <Arduino.h>
#include <OLEDDisplayUi.h>


class Meter {
public:
  void begin();
  void handle();
  void interrupt();
  void reset();
  double getDistance();
  double getSpeed();
  String getFormatedDistance();
  String getFormatedSpeed();
  String getFormatedTime();

private:
  double _cycles = 0;
};

#endif
