
#include <Wire.h>
#define _MSGS_LENGTH 8
#define I2CsendBuffer_SIZE 64

//#define DEBUGG

byte I2CsendBuffer[I2CsendBuffer_SIZE];
int I2CsendBuffer_head = 0;
int I2CsendBuffer_tail = 0;


int fifo_byte_available();
int _fifo_enqueue(byte b);

// Returns the number of byte currently in the I2CsendBuffer
int I2CsendBuffer_byte_length() {
  if (I2CsendBuffer_tail >= I2CsendBuffer_head)
    return I2CsendBuffer_tail - I2CsendBuffer_head;
  return I2CsendBuffer_tail + I2CsendBuffer_SIZE - I2CsendBuffer_head;
}

// Returns the number of bytes currently available in the I2CsendBuffer
int I2CsendBuffer_byte_available() {
  return I2CsendBuffer_SIZE - 1 - I2CsendBuffer_byte_length();
}

// Returns true if the I2CsendBuffer is empty
int I2CsendBuffer_empty() {
  return I2CsendBuffer_head == I2CsendBuffer_tail;
}

// Return true if the I2CsendBuffer is full
int I2CsendBuffer_full() {
  return I2CsendBuffer_head == ((I2CsendBuffer_tail + 1) % I2CsendBuffer_SIZE);
}

// Enqueue 1 byte in the I2CsendBuffer if there is space
// returns 1 for sucess and 0 if the I2CsendBuffer was full
int I2CsendBuffer_enqueue(byte b) {
  int new_tail = (I2CsendBuffer_tail + 1) % I2CsendBuffer_SIZE;
  if (new_tail == I2CsendBuffer_head) return 0; // the I2CsendBuffer is full
  I2CsendBuffer[I2CsendBuffer_tail] = b;
  I2CsendBuffer_tail = new_tail;
  return 1;
}

// Enqueue 1 byte in the I2CsendBuffer without checking for available space
// The caller should have checked that there is enough space
int _I2CsendBuffer_enqueue(byte b) {
  I2CsendBuffer[I2CsendBuffer_tail] = b;
  I2CsendBuffer_tail = (I2CsendBuffer_tail + 1) % I2CsendBuffer_SIZE;
}

// Dequeue 1 byte in the I2CsendBuffer.
// The caller should check that the I2CsendBuffer is not empty
byte I2CsendBuffer_dequeue() {
  if (!I2CsendBuffer_empty()) {
    byte result = I2CsendBuffer[I2CsendBuffer_head];
    I2CsendBuffer_head = (I2CsendBuffer_head + 1) % I2CsendBuffer_SIZE;
    return result;
  }
  return 0;
}




void I2Cread() {
  
  #ifdef DEBUGG
    Serial.println("[I2Cread] Start");
  #endif
  
   while (Wire.available())   // slave may send less than requested
    {
      byte b = Wire.read(); // receive a byte
      _fifo_enqueue(b);
    }
  
    #ifdef DEBUGG
      Serial.println();
      Serial.println("[I2Cread] Done ");
    #endif
  
}

void I2CrequestEvent() {
  #ifdef DEBUGG
    Serial.print("[requested to talk]");
  #endif
  
  
  if(!I2CsendBuffer_empty()) {
    byte msglength = I2CsendBuffer_dequeue();
    #ifdef DEBUGG
      Serial.print(" ");
      Serial.print(msglength);
    #endif
    byte msgToSendBuffer[msglength];
    msgToSendBuffer[0] = msglength;
    
    for(byte i = 1; i < msglength+1; i++) {
      msgToSendBuffer[i] = I2CsendBuffer_dequeue();
      #ifdef DEBUGG
        Serial.print(" ");
        Serial.print(msgToSendBuffer[i]);
      #endif
      
    }
    Wire.write(msgToSendBuffer, msglength+1);
  }
  #ifdef DEBUGG
    Serial.println(" Done.");
  #endif
}

void I2CreceiveEvent(int l) {
  #ifdef DEBUGG
    Serial.println("[listening]");
  #endif
  I2Cread();
}

void setup_I2C() {
  
  #ifdef DEBUGG
    Serial.begin(9600);
    Serial.println("[setup_I2C]");
  #endif
  
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(I2CrequestEvent); // register event
  Wire.onReceive(I2CreceiveEvent);
  // Init the adresse table
}
