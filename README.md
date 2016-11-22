# digi-rc-switch

[![Build Status](https://travis-ci.org/solarkennedy/digi-rc-switch.svg?branch=master)](https://travis-ci.org/solarkennedy/digi-rc-switch)

Code to use a Digispark (ATtiny85) to send rc-switch RF codes over a 433mhz
transmitter via USB.

## Operation

When operating, the device shows up as a serial port. Sending the 4 bytes (long)
to the serial port initiate the RF code transmission.

## Hardware

* [433mhz FSK Transmitter](https://www.sparkfun.com/products/10534)
* [Digispark](http://digistump.com/products/1)

```
Transmitter   Digispark
GND  -------- GND
VCC  -------- VCC
DATA -------- PIN1
```

## Software

Uses the [rc-switch](https://github.com/sui77/rc-switch) library to send
RF codes.

See the `python-driver` directory for a python script to send RF codes
