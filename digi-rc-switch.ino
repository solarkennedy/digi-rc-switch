#include <RCSwitch.h>

#define USB_CFG_DEVICE_NAME     'D','i','g','i','B','l','i','n','k'
#define USB_CFG_DEVICE_NAME_LEN 9
#include <DigiUSB.h>


RCSwitch mySwitch = RCSwitch();
byte in = 0;
byte byte1 = 0;
byte byte2 = 0;
byte byte3 = 0;
int next = 0;
long code = 0;


// The rc-switch library requires a long int, but we can only
// read data out of the usb 1 bytes at a time, so we must
// compose our own long to send to rc-switch
long composeLong(byte one, byte two, byte three){
  return (long) one << 16 | (long) two << 8 | (long) three;
}

void setup() {
  DigiUSB.begin();
  mySwitch.enableTransmit(0);
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
      code = composeLong(byte1, byte2, byte3);
      DigiUSB.print("Sending Code:");
      DigiUSB.println(code, HEX);
      mySwitch.send(code, 24);
      next = 0;
    } else {
      DigiUSB.print("Else Got:");
      DigiUSB.println(in, HEX);
    }
  }

}
