#ifndef ArduinoI2CForwardMster_h
#define ArduinoI2CForwardMster_h

#include <Wire.h>

#include "ArduinoI2CForwardMaster.c"

void setup_I2C();

void I2Csend(byte addr);

void I2CaddToSendBuffer(byte b);

void I2Cread();

#endif
