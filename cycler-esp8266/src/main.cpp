#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Wire.h>


#include <OLEDDisplayUi.h>
#include <SH1106Wire.h>


#include "fonts.h"
#include "images.h"


// OTA Settings
bool upgrading = false;
int upgradingProgress = 0;

// OLED Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D2;
const int SDC_PIN = D1;
const int OLED_BRIGHTNESS = 128;
SH1106Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);
OLEDDisplayUi ui(&display);


void drawProgress(OLEDDisplay *display, int percentage, String label);


void setupDisplay() {
  display.init();
  display.clear();
  display.flipScreenVertically();
  display.display();

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setContrast(OLED_BRIGHTNESS);
}

void setupOTA() {
  ArduinoOTA.begin();
  ArduinoOTA.onStart([]() {
    upgrading = true;
    upgradingProgress = 0;
    Serial.println("Uploading firmware...");
    display.displayOn();
    display.setContrast(255);
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
    drawProgress(&display, upgradingProgress, "Done");
    delay(500);
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
    delay(500);
    Serial.print(".");
    display.clear();
    display.drawString(64, 10, "Connecting to WiFi");
    display.drawXbm(46, 30, 8, 8, counter % 3 == 0 ? activeSymbole : inactiveSymbole);
    display.drawXbm(60, 30, 8, 8, counter % 3 == 1 ? activeSymbole : inactiveSymbole);
    display.drawXbm(74, 30, 8, 8, counter % 3 == 2 ? activeSymbole : inactiveSymbole);
    display.flipScreenVertically();
    display.display();
    counter++;
  }
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
}


void drawProgress(OLEDDisplay *display, int percentage, String label) {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawProgressBar(2, 28, 124, 10, percentage);
  display->flipScreenVertically();
  display->display();
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("cycler-esp8266 is now setting up...");

  // Initialize dispaly
  setupDisplay();
  setupWiFi();
  setupOTA();
}

void loop() {
  ArduinoOTA.handle();
  if (upgrading) {
    return;
  }
}
