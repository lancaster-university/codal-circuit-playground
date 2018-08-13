/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef CIRCUIT_PLAYGROUND_IO_H
#define CIRCUIT_PLAYGROUND_IO_H

#include "mbed.h"
#include "CodalConfig.h"
#include "MbedPin.h"

//
// Component IDs for each pin.
// The can be user defined, but uniquely identify a pin when using the eventing APIs/
//
#define ID_PIN_A0           (DEVICE_ID_IO_P0 + 0)
#define ID_PIN_A1           (DEVICE_ID_IO_P0 + 1)
#define ID_PIN_A2           (DEVICE_ID_IO_P0 + 2)
#define ID_PIN_A3           (DEVICE_ID_IO_P0 + 3)
#define ID_PIN_A4           (DEVICE_ID_IO_P0 + 4)
#define ID_PIN_A5           (DEVICE_ID_IO_P0 + 5)
#define ID_PIN_A6           (DEVICE_ID_IO_P0 + 6)
#define ID_PIN_A7           (DEVICE_ID_IO_P0 + 7)
#define ID_PIN_SCL          (ID_PIN_A4)
#define ID_PIN_SDA          (ID_PIN_A5)
#define ID_PIN_RX           (ID_PIN_A6)
#define ID_PIN_TX           (ID_PIN_A7)
#define ID_PIN_LED          (DEVICE_ID_IO_P0 + 19)
#define ID_PIN_SPEAKER      (DEVICE_ID_IO_P0 + 20)
#define ID_PIN_THERMISTOR   (DEVICE_ID_IO_P0 + 21)
#define ID_PIN_LIGHTSENSOR  (DEVICE_ID_IO_P0 + 22)
#define ID_PIN_INT1         (DEVICE_ID_IO_P0 + 23)
#define ID_PIN_BUTTONA      (DEVICE_ID_IO_P0 + 24)
#define ID_PIN_BUTTONB      (DEVICE_ID_IO_P0 + 25)
#define ID_PIN_BUTTONC      (DEVICE_ID_IO_P0 + 26)
#define ID_PIN_TOUCHDRIVE   (DEVICE_ID_IO_P0 + 27)
#define ID_PIN_MIC_DATA     (DEVICE_ID_IO_P0 + 28)
#define ID_PIN_MIC_CLOCK    (DEVICE_ID_IO_P0 + 29)
#define ID_PIN_NEOPIXEL     (DEVICE_ID_IO_P0 + 30)
#define ID_PIN_FLASH_MISO   (DEVICE_ID_IO_P0 + 31)
#define ID_PIN_FLASH_MOSI   (DEVICE_ID_IO_P0 + 32)
#define ID_PIN_FLASH_SCLK   (DEVICE_ID_IO_P0 + 33)
#define ID_PIN_FLASH_SSEL   (DEVICE_ID_IO_P0 + 34)

#define DEVICE_ID_BUTTON_C            1024

namespace codal
{
    /**
      * Represents a collection of all I/O pins exposed by the device.
      */
    class CircuitPlaygroundIO
    {
        public:

        codal::_mbed::Pin          pin[0];
        codal::_mbed::Pin          a0;
        codal::_mbed::Pin          a1;
        codal::_mbed::Pin          a2;
        codal::_mbed::Pin          a3;
        codal::_mbed::Pin          a4;
        codal::_mbed::Pin          a5;
        codal::_mbed::Pin          a6;
        codal::_mbed::Pin          a7;
        codal::_mbed::Pin          speaker;
        codal::_mbed::Pin          microphoneData;
        codal::_mbed::Pin          microphoneClock;
        codal::_mbed::Pin          led;
        codal::_mbed::Pin          int1;
        codal::_mbed::Pin          temperature;
        codal::_mbed::Pin          light;
        codal::_mbed::Pin          buttonA;
        codal::_mbed::Pin          buttonB;
        codal::_mbed::Pin          buttonC;
        codal::_mbed::Pin          sda;
        codal::_mbed::Pin          scl;
        codal::_mbed::Pin          neopixel;
        codal::_mbed::Pin          flashMISO;
        codal::_mbed::Pin          flashMOSI;
        codal::_mbed::Pin          flashSCLK;
        codal::_mbed::Pin          flashSSEL;

        /**
          * Constructor.
          *
          * Create a representation of all given I/O pins on the edge connector
          *
          */
        CircuitPlaygroundIO();
    };
}

#endif
