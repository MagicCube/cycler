#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Wire.h>


#include <OLEDDisplayUi.h>
#include <SH1106Wire.h>
#include <TimeClient.h>


#include "fonts.h"
#include "HttpService.h"
#include "images.h"
#include "Meter.h"
#include "StopWatch.h"


void drawProgress(OLEDDisplay *display, int percentage, String label);
void drawMain(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);
void drawOverlay(OLEDDisplay *display, OLEDDisplayUiState *state);

// General settings
const bool OFFLINE = true;
const bool SIMULATING = true;

// States
int sim_millis = 0;
int last_zero_millis = 0;

// Time Client
const int UTC_OFFSET = 8;
TimeClient timeClient(UTC_OFFSET);

// Meter
const int SENSOR_PIN = D3;
Meter meter;

// StopWatch
StopWatch stopWatch;

// HTTP Service
HttpService service(&meter, &stopWatch);

// OTA Settings
bool upgrading = false;
int upgradingProgress = 0;

// OLED Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D2;
const int SDC_PIN = D1;
const int OLED_BRIGHTNESS = 96;
SH1106Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
OLEDDisplayUi ui(&display);

// Add frames
// this array keeps function pointers to all frames
// frames are the single views that slide from right to left
FrameCallback frames[] = {drawMain};
int numberOfFrames = 1;
OverlayCallback overlays[] = {drawOverlay};
int numberOfOverlays = 1;


void setupDisplay() {
  display.init();
  display.clear();
  display.flipScreenVertically();
  display.display();

  display.setTextAlignment(TEXT_ALIGN_CENTER);

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 15, "SMART CYCLER");
  display.setFont(ArialMT_Plain_10);
  display.drawString(64, 35, "by Henry");
  display.display();
}

void setupOTA() {
  ArduinoOTA.begin();
  ArduinoOTA.onStart([]() {
    upgrading = true;
    upgradingProgress = 0;
    Serial.println("Uploading firmware...");
    drawProgress(&display, 0, "Uploading firmware...");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    upgradingProgress = progress / (total / 100);
    Serial.print(upgradingProgress);
    Serial.println("%");
    drawProgress(&display, upgradingProgress, "Uploading firmware...");
  });
  ArduinoOTA.onEnd([]() {
    upgradingProgress = 100;
    Serial.println("Done. Ready to restart.");
    drawProgress(&display, upgradingProgress, "Restarting...");
  });
}

void setupWiFi() {
  Serial.println("Scanning WiFi...");
  WiFi.mode(WIFI_STA);
  // Auto scan WiFi connection
  String prefSSID = "none";
  String prefPassword;
  int ssidCount = WiFi.scanNetworks();
  if (ssidCount == -1) {
    return;
  }
  for (int i = 0; i < ssidCount; i++) {
    String ssid = WiFi.SSID(i);
    if (ssid.equals("Henry's Living Room 2.4GHz")) {
      prefSSID = ssid;
      prefPassword = "13913954971";
      break;
    } else if (ssid.equals("Henry's TP-LINK")) {
      prefSSID = ssid;
      prefPassword = "13913954971";
      break;
    } else if (ssid.equals("Henry's iPhone 6")) {
      prefSSID = ssid;
      prefPassword = "13913954971";
      // Don't break, cause this will connect to 4G network.
      // It's absolutely not a first choise.
    }
  }
  if (prefSSID.equals("none")) {
    return;
  }
  Serial.print("Connecting to ");
  Serial.print(prefSSID.c_str());
  WiFi.begin(prefSSID.c_str(), prefPassword.c_str());

  int counter = 0;
  display.setFont(ArialMT_Plain_10);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    display.clear();
    display.drawString(64, 10, "Connecting to WiFi");
    display.drawXbm(46, 30, 8, 8, counter % 3 == 0 ? activeSymbole : inactiveSymbole);
    display.drawXbm(60, 30, 8, 8, counter % 3 == 1 ? activeSymbole : inactiveSymbole);
    display.drawXbm(74, 30, 8, 8, counter % 3 == 2 ? activeSymbole : inactiveSymbole);
    display.display();
    counter++;
    delay(500);
  }
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());

  service.begin();
}

void setupUI() {
  ui.setTargetFPS(30);
  // ui.setActiveSymbol(activeSymbole);
  // ui.setInactiveSymbol(inactiveSymbole);
  // ui.setIndicatorPosition(BOTTOM);
  // ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, numberOfFrames);
  ui.setOverlays(overlays, numberOfOverlays);
  ui.setTimePerTransition(360);
  ui.setTimePerFrame(10 * 1000);
  ui.disableAllIndicators();
  ui.disableAutoTransition();
  ui.init();
}

void setupTime() {
  drawProgress(&display, 10, "Updating time...");
  timeClient.updateTime();
}


void drawProgress(OLEDDisplay *display, int percentage, String label) {
  display->flipScreenVertically();
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawProgressBar(2, 28, 124, 10, percentage);
  display->display();
}

void drawMain(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_16);
  display->drawString(x + 64, y, stopWatch.getFormatedElapsed());

  display->setFont(ArialMT_Plain_24);
  display->drawString(x + 64, y + 22, meter.getFormatedDistance());

  display->setTextAlignment(TEXT_ALIGN_LEFT);
}

void drawOverlay(OLEDDisplay *display, OLEDDisplayUiState *state) {
  display->setColor(WHITE);
  display->setFont(ArialMT_Plain_10);
  String time = timeClient.getFormattedTime().substring(0, 5);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 54, time);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  if (stopWatch.getState() != StopWatch::PAUSED) {
    display->drawString(127, 54, meter.getFormatedSpeed());
  } else {
    display->drawString(127, 54, "PAUSED");
  }
  display->drawHorizontalLine(0, 53, 128);
}

void checkPause() {
  // Auto pause at 5 seconds after there's no actions detected
  if (meter.getSpeed() == 0 && last_zero_millis == 0) {
    last_zero_millis = millis();
  } else {
    last_zero_millis = 0;
  }
  if (last_zero_millis != 0 && millis() - last_zero_millis > 5000) {
    stopWatch.pause();
  }
}

int lastInterrupt = 0;
void sensorInterrupt() {
  if (!stopWatch.isRunning()) {
    stopWatch.start();
  }
  int now = millis();
  if (lastInterrupt == millis()) {
    return;
  } else {
    lastInterrupt = now;
  }
  meter.interrupt();
  Serial.println(timeClient.getFormattedTime());
}


void setup() {
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(SENSOR_PIN, sensorInterrupt, FALLING);

  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("cycler-esp8266 is now setting up...");

  setupDisplay();
  if (!OFFLINE) {
    setupWiFi();
    setupOTA();
    setupTime();
  }
  setupUI();

  display.flipScreenVertically();
  display.setContrast(OLED_BRIGHTNESS);

  meter.begin();

  if (SIMULATING) {
    sim_millis = millis();
  }
}

void loop() {
  if (!OFFLINE) {
    ArduinoOTA.handle();
    if (upgrading) {
      return;
    }
  }

  if (SIMULATING) {
    if (millis() - sim_millis > 300 + random(500)) {
      sim_millis = millis();
      sensorInterrupt();
    }
  }

  checkPause();

  meter.handle();
  service.handle();

  int remainingTimeBudget = ui.update();
  if (remainingTimeBudget > 0) {
    // delay(remainingTimeBudget);
  }
}
