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

/**
  * Class definition for Genuino Zero IO.
  * Represents a collection of all I/O pins on the device.
  */

#include "CodalConfig.h"
#include "CircuitPlaygroundIO.h"

#include "sam.h"

using namespace codal;

/**
  * Constructor.
  *
  * Create a representation of all given I/O pins on the edge connector
  *
  * Accepts a sequence of unique ID's used to distinguish events raised
  * by MicroBitPin instances on the default EventModel.
  */
CircuitPlaygroundIO::CircuitPlaygroundIO() :
    a0 (ID_PIN_A0, PIN_PA02, PIN_CAPABILITY_AD),
    a1 (ID_PIN_A1, PIN_PA05, PIN_CAPABILITY_AD),
    a2 (ID_PIN_A2, PIN_PA06, PIN_CAPABILITY_AD),
    a3 (ID_PIN_A3, PIN_PA07, PIN_CAPABILITY_AD),
    a4 (ID_PIN_A4, PIN_PB03, PIN_CAPABILITY_AD),
    a5 (ID_PIN_A5, PIN_PB02, PIN_CAPABILITY_AD),
    a6 (ID_PIN_A6, PIN_PB09, PIN_CAPABILITY_AD),
    a7 (ID_PIN_A7, PIN_PB08, PIN_CAPABILITY_AD),
    speaker (ID_PIN_SPEAKER, PIN_PA02, PIN_CAPABILITY_AD),
    microphoneData (ID_PIN_MIC_DATA, PIN_PA08, PIN_CAPABILITY_AD),
    microphoneClock (ID_PIN_MIC_CLOCK, PIN_PA10, PIN_CAPABILITY_AD),
    led (ID_PIN_LED, PIN_PA17, PIN_CAPABILITY_DIGITAL),
    int1(ID_PIN_INT1, PIN_PA13, PIN_CAPABILITY_DIGITAL),
    temperature(ID_PIN_THERMISTOR, PIN_PA09, PIN_CAPABILITY_AD),
    light(ID_PIN_LIGHTSENSOR, PIN_PA11, PIN_CAPABILITY_AD),
    buttonA(ID_PIN_BUTTONA, PIN_PA28, PIN_CAPABILITY_DIGITAL),
    buttonB(ID_PIN_BUTTONB, PIN_PA14, PIN_CAPABILITY_DIGITAL),
    buttonC(ID_PIN_BUTTONC, PIN_PA15, PIN_CAPABILITY_DIGITAL),
    sda(ID_PIN_SDA, PIN_PA00, PIN_CAPABILITY_DIGITAL),
    scl(ID_PIN_SCL, PIN_PA01, PIN_CAPABILITY_DIGITAL),
    neopixel(ID_PIN_NEOPIXEL, PIN_PB23, PIN_CAPABILITY_DIGITAL),
    flashMISO(ID_PIN_FLASH_MISO, PIN_PA16, PIN_CAPABILITY_DIGITAL),
    flashMOSI(ID_PIN_FLASH_MOSI, PIN_PA20, PIN_CAPABILITY_DIGITAL),
    flashSCLK(ID_PIN_FLASH_SCLK, PIN_PA21, PIN_CAPABILITY_DIGITAL),
    flashSSEL(ID_PIN_FLASH_SSEL, PIN_PB22, PIN_CAPABILITY_DIGITAL)
{
}
