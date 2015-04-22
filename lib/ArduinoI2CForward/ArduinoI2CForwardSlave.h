#ifndef ArduinoI2CForwardSlave_h

#define ArduinoI2CForwardSlave_h
#include "ArduinoI2CForwardSlave.c"

int I2CsendBuffer_byte_length();
int I2CsendBuffer_byte_available();
int I2CsendBuffer_empty();
int I2CsendBuffer_full();
int I2CsendBuffer_enqueue(byte b);
int _I2CsendBuffer_enqueue(byte b);
byte I2CsendBuffer_dequeue();

void I2Cread();
void I2CrequestEvent();
void I2CreceiveEvent(int l);
void setup_I2C();

#endif
