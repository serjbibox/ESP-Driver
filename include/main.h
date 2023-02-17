#ifndef __MAIN_H
#define __MAIN_H
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AccelStepper.h>

typedef struct{
  uint16_t revolution;
  boolean direction;
  uint8_t maxSpeed;
  uint16_t maxPosition;
  uint16_t minPosition;
  float accel;
  boolean autoHome;
  uint8_t length;
}Settings_t;

typedef struct{
  float speed;
  float accel;
  long dest;
}Stepper_t;


typedef struct{
  boolean isMove;
  boolean isHomed;
  boolean isMaxPos;
  boolean isMinPos;
  uint16_t currentPosition;
  uint16_t currentSpeed;
  boolean isHomeProcess;
  boolean isHoming;
  boolean isOnHomeSensor;
  boolean isOnUpSensor;
}State_t;

typedef struct{
  uint8_t workTime;
  uint16_t workSpeed;
  uint16_t destPosition;
  boolean workType;
  boolean start;
  boolean power;
  boolean save;
  boolean home;
  boolean moveLeft;
  boolean moveRight;
}Control_t;

typedef struct{
    char ssid[30];// = "TP-LINK_8D8B26";
    char password[30];// = "15394255";
}WifiSettings_t;

#endif