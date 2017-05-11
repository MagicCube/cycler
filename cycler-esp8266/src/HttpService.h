#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "Meter.h"
#include "StopWatch.h"

#include <ESP8266WebServer.h>
class HttpService
{
  public:
    HttpService(Meter *meter, StopWatch *stopWatch);
    void begin();
    void handle();

  private:
    ESP8266WebServer _server;
    Meter *_meter;
    StopWatch *_stopWatch;
};
#endif
