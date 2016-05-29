#!/usr/bin/python
import usb
import sys

sys.path.append("..")
from arduino.usbdevice import ArduinoUsbDevice


def sendCode(code):
    theDevice.write(ord("s"))
    # TODO breakup into bytes
    theDevice.write(code)


def validateCode(code):
    # TODO: validate the code can fit into a 24bit long
    pass


def printHelp():
    pass

if __name__ == "__main__":
    theDevice = ArduinoUsbDevice(idVendor=0x16c0, idProduct=0x05df)
    print "Found: 0x%04x 0x%04x %s %s" % (
        theDevice.idVendor, 
        theDevice.idProduct,
        theDevice.productName,
        theDevice.manufacturer
    )

    if len(sys.argv) != 2:
        printHelp
    else:
        code=sys.argv[1]
        validateCode(code)
        sendCode(code)
