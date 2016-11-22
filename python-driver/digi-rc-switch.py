#!/usr/bin/python
import sys
import struct

sys.path.append(".")
from arduino.usbdevice import ArduinoUsbDevice


def codeToBytes(code):
    return struct.unpack("4B", struct.pack("I", code))


def sendCode(code):
    print "Sending %s" % str(code)
    for byte in codeToBytes(code):
        print "  Sending byte %s" % hex(byte)
        theDevice.write(byte)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "Usage: %s CODE"
        print "CODE must be a 32 bit int."
    else:
        theDevice = ArduinoUsbDevice(idVendor=0x16c0, idProduct=0x05df)
        print "Found: 0x%04x 0x%04x %s %s" % (
            theDevice.idVendor,
            theDevice.idProduct,
            theDevice.productName,
            theDevice.manufacturer
        )
        code=int(sys.argv[1])
        sendCode(code)
