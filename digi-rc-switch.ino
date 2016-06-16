#include <RCSwitch.h>
#include <DigiUSB.h>

RCSwitch mySwitch = RCSwitch();
byte in = 0;
byte byte1 = 0;
byte byte2 = 0;
byte byte3 = 0;
byte byte4 = 0;
int next = 0;
long code = 0;


// The rc-switch library requires a long int, but we can only
// read data out of the usb 1 bytes at a time, so we must
// compose our own long to send to rc-switch
long composeLong(byte one, byte two, byte three, byte four) {
  return (long) four << 24 | (long) three << 16 | (long) two << 8 | (long) one;
}

void setup() {
  DigiUSB.begin();
  mySwitch.enableTransmit(1);
  mySwitch.setPulseLength(192);
}

void loop() {
  DigiUSB.refresh();
  if (DigiUSB.available() > 0) {
    in = DigiUSB.read();
    if (next == 0) {
      if (in == 115) {
        next = 1;
        DigiUSB.println("Start");
      }
    }
    else if (next == 1) {
      byte1 = in;
      DigiUSB.print("byte1 ");
      DigiUSB.println(in, HEX);
      next = 2;
    }
    else if (next == 2) {
      byte2 = in;
      DigiUSB.print("byte2 ");
      DigiUSB.println(in, HEX);
      next = 3;
    }
    else if (next == 3) {
      byte3 = in;
      DigiUSB.print("byte3 ");
      DigiUSB.println(in, HEX);
      next = 4;
    }
    else if (next == 4) {
      byte4 = in;
      DigiUSB.print("byte4 ");
      DigiUSB.println(in, HEX);
      code = composeLong(byte1, byte2, byte3, byte4);
      DigiUSB.print("Sending Code:");
      DigiUSB.print(code);
      DigiUSB.print(" (hex: ");
      DigiUSB.print(code, HEX);
      DigiUSB.print(")...");
      mySwitch.send(code, 24);
      DigiUSB.println("Done");
      next = 0;
    } else {
      DigiUSB.print("Else Got:");
      DigiUSB.println(in, HEX);
    }
  }
}
