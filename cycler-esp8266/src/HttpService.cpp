#include "HttpService.h"

#include <ESP8266WebServer.h>

HttpService::HttpService(Meter *meter, StopWatch *stopWatch) : _server(80) {
  this->_meter = meter;
  this->_stopWatch = stopWatch;
}

void HttpService::begin() {
  _server.on("/api/states", HTTP_GET, [ this ]() {
    _server.send(200, "application/json", "[]");
  });

  _server.on("/api/speed", HTTP_GET, [ this ]() {
    _server.send(200, "application/json", "[]");
  });
  
  _server.begin();
}

void HttpService::handle() {
  _server.handleClient();
}
