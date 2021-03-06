#include <Wire.h>
#define _NB_SLAVES 1
#define _MSGS_LENGTH 8

//#define DEBUGG

byte I2Caddr[_NB_SLAVES];
byte I2CsendBuffer[_MSGS_LENGTH];
byte I2CsendBufferIndice = 0;


int fifo_byte_available();
int _fifo_enqueue(byte b);

void setup_I2C() {
  
  #ifdef DEBUGG
    Serial.println("[setup_I2C]");
  #endif
  
  Wire.begin();
  // Init the adresse table
  I2Caddr[0] = 2;
}

void I2Csend(byte addr) {
  
  #ifdef DEBUGG
    Serial.print("[I2Csend] to: ");
  #endif
  
  Wire.beginTransmission(addr);
  
  #ifdef DEBUGG
    Serial.print(addr);
    Serial.print(" -> ");
  #endif
  
  for (byte i = 0; i < I2CsendBufferIndice; i++) {
    #ifdef DEBUGG
      Serial.print(I2CsendBuffer[i]);
      Serial.print(" ");
    #endif
    Wire.write(I2CsendBuffer[i]);
  }
  Wire.endTransmission();
  I2CsendBufferIndice = 0;
  
  #ifdef DEBUGG
    Serial.println();
  #endif
}

void I2CaddToSendBuffer(byte b) {
  
  #ifdef DEBUGG
    Serial.print("[I2CaddToBuffer] ");
  #endif
  
  if(I2CsendBufferIndice < _MSGS_LENGTH) {
  
    #ifdef DEBUGG
      Serial.print(b);
    #endif
  
    I2CsendBuffer[I2CsendBufferIndice] = b;
    I2CsendBufferIndice++;
  }
  
  #ifdef DEBUGG
    Serial.println();
  #endif
}

void I2Cread() {
  
  #ifdef DEBUGG
    Serial.println("[I2Cread] Start");
  #endif
  
  // Every slave will be ask to send one message
  for(byte i = 0; i < _NB_SLAVES; i++) {
  
    #ifdef DEBUGG
      Serial.print("[I2Cread] listening ");
      Serial.print(I2Caddr[i]);
      Serial.print(" -> ");
    #endif
    
    byte l = 0;
    Wire.requestFrom((int) I2Caddr[i], _MSGS_LENGTH);    // request 6 bytes from slave device #2
    byte lengthCurMsg = Wire.read();
    
    #ifdef DEBUGG
      Serial.print("[");
      Serial.print(lengthCurMsg);
      Serial.print("] ");
    #endif
    
    while (Wire.available() && (l < lengthCurMsg))   // slave may send less than requested
    {
      byte b = Wire.read(); // receive a byte
      _fifo_enqueue(b);
      l++;
    }
  }
  
    #ifdef DEBUGG
      Serial.println();
      Serial.println("[I2Cread] Done ");
    #endif
  
}
