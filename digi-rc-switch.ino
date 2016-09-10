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
      SerialUSB.println("Start");
      next = 1;
      last_time = millis();
    }
    in = SerialUSB.read();

    if (next == 1) {
      byte1 = in;
      SerialUSB.print(F("byte1 "));
      SerialUSB.println(in, HEX);
      next = 2;
    }
    else if (next == 2) {
      byte2 = in;
      SerialUSB.print(F("byte2 "));
      SerialUSB.println(in, HEX);
      next = 3;
    }
    else if (next == 3) {
      byte3 = in;
      SerialUSB.print(F("byte3 "));
      SerialUSB.println(in, HEX);
      next = 4;
    }
    else if (next == 4) {
      byte4 = in;
      SerialUSB.print(F("byte4 "));
      SerialUSB.println(in, HEX);
      code = composeLong(byte1, byte2, byte3, byte4);
      SerialUSB.print(F("Sending Code:"));
      SerialUSB.print(code);
      SerialUSB.print(F(" (hex: "));
      SerialUSB.print(code, HEX);
      SerialUSB.print(F(")..."));
      mySwitch.send(code, 24);
      SerialUSB.println(F("Done"));
      SerialUSB.println("");
      next = 0;
    } else {
      SerialUSB.print(F("Else Got:"));
      SerialUSB.println(in, HEX);
    }
  }
  SerialUSB.refresh();
}
