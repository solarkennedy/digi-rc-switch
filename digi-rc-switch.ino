#include <RCSwitch.h>
#include <DigiCDC.h>

RCSwitch mySwitch = RCSwitch();
byte in = 0;
byte byte1 = 0;
byte byte2 = 0;
byte byte3 = 0;
byte byte4 = 0;
int next = 0;
long code = 0;
long last_time = 0;


// The debug print code interferes with the stability
// of the usb thing, the attiny can't print out reliably.
#define DEBUG 0

// The rc-switch library requires a long int, but we can only
// read data out of the usb 1 bytes at a time, so we must
// compose our own long to send to rc-switch
long composeLong(byte one, byte two, byte three, byte four) {
  return (long) four << 24 | (long) three << 16 | (long) two << 8 | (long) one;
}

void setup() {
  SerialUSB.begin();
  mySwitch.enableTransmit(1);
  mySwitch.setPulseLength(192);
  last_time = millis();
}

void loop() {

  if (SerialUSB.available()) {
    if (last_time <= millis() - 1000) {
      #ifdef DEBUG
      SerialUSB.println("Start");
      #endif
      next = 1;
      last_time = millis();
    }
    in = SerialUSB.read();

    if (next == 1) {
      byte1 = in;
      #ifdef DEBUG
      SerialUSB.print(F("byte1 "));
      SerialUSB.println(in, HEX);
      #endif
      next = 2;
    }
    else if (next == 2) {
      byte2 = in;
      #ifdef DEBUG
      SerialUSB.print(F("byte2 "));
      SerialUSB.println(in, HEX);
      #endif
      next = 3;
    }
    else if (next == 3) {
      byte3 = in;
      #ifdef DEBUG
      SerialUSB.print(F("byte3 "));
      SerialUSB.println(in, HEX);
      #endif
      next = 4;
    }
    else if (next == 4) {
      byte4 = in;
      #ifdef DEBUG
      SerialUSB.print(F("byte4 "));
      SerialUSB.println(in, HEX);
      #endif
      code = composeLong(byte1, byte2, byte3, byte4);
      #ifdef DEBUG
      SerialUSB.print(F("Sending Code:"));
      SerialUSB.print(code);
      SerialUSB.print(F(" (hex: "));
      SerialUSB.print(code, HEX);
      SerialUSB.print(F(")..."));
      #endif
      mySwitch.send(code, 24);
      #ifdef DEBUG
      SerialUSB.println(F("Done"));
      SerialUSB.println("");
      #endif
      next = 0;
    #ifdef DEBUG
    } else {
      SerialUSB.print(F("Else Got:"));
      SerialUSB.println(in, HEX);
    #endif
    }
  }
  SerialUSB.refresh();
}
