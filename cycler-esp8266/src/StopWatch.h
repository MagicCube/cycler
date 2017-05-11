#ifndef stop_watch_h
#define stop_watch_h

#include <Arduino.h>


class StopWatch {
public:
  enum State { STOPPED, RUNNING, PAUSED };
  void start();
  void pause();
  void reset();
  int getElapsed();
  State getState();
  bool isRunning();
  String getFormatedElapsed();

private:
  State _state = STOPPED;
  int _startTime = 0;
  int _accElapsed = 0;
};

String formatDigit2(int num);

#endif
