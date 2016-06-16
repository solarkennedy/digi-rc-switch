# digi-rc-switch

Code to use a Digispark (ATtiny85) to send rc-switch RF codes over a 433mhz
transmitter via USB.

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

See the `python-driver` directory for a python script to send RF codes
