#!/usr/bin/python
import sys
import struct

import serial
sys.path.append("..")
from arduino.usbdevice import ArduinoUsbDevice


def codeToBytes(code):
    return struct.unpack("4B", struct.pack("I", code))


def sendCode(code, serial):
    print "Sending %s" % str(code)
    for byte in codeToBytes(code):
        print "  Sending byte %s (dec %s)" % (hex(byte), str(byte))
        serial.write([byte])


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "Usage: %s CODE"
        print "CODE must be a 32 bit int."
    else:
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        ser.close()
        ser.open()
        code=int(sys.argv[1])
        sendCode(code, ser)
        ser.close()
