#include "HttpService.h"

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

StaticJsonBuffer<1024> jsonBuffer;

HttpService::HttpService(Meter *meter, StopWatch *stopWatch) : _server(80) {
  this->_meter = meter;
  this->_stopWatch = stopWatch;
}

void HttpService::begin() {
  this->_server.on("/api/now", HTTP_GET, [ this ]() {
    JsonObject& json = jsonBuffer.createObject();
    json["speed"] = this->_meter->getTantaneousSpeed();
    json["distance"] = this->_meter->getDistance();
    json["elapsed"] = this->_stopWatch->getElapsed() / 1000;
    json["state"] = (int)this->_stopWatch->getState();
    String jsonString;
    json.printTo(jsonString);
    this->_server.send(200, "application/json", jsonString);
  });

  this->_server.on("/api/speed", HTTP_GET, [ this ]() {
    JsonArray& json = jsonBuffer.createArray();
    list<float> records = this->_meter->getSpeedRecords();
    for (auto it = records.begin(); it != records.end(); ++it) {
      json.add(*it);
    }
    String jsonString;
    json.printTo(jsonString);
    this->_server.send(200, "application/json", jsonString);
  });

  this->_server.on("/api/reset", HTTP_POST, [ this ]() {
    this->_stopWatch->reset();
    this->_meter->reset();
    this->_server.send(200, "text/plain", "OK");
  });

  this->_server.begin();
}

void HttpService::handle() {
  this->_server.handleClient();
}
