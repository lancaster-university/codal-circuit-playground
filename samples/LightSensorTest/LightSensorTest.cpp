/*
The MIT License (MIT)

Copyright (c) 2016 Lancaster University.

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

#include "CircuitPlayground.h"

CircuitPlayground cplay;

void onBright(DeviceEvent)
{
    cplay.serial.printf("*** BRIGHT ***\n");
}

void onDark(DeviceEvent)
{
    cplay.serial.printf("*** DARK ***\n");
}

int main()
{
    cplay.messageBus.listen(DEVICE_ID_LIGHT_SENSOR, ANALOG_THRESHOLD_HIGH, onBright);
    cplay.messageBus.listen(DEVICE_ID_LIGHT_SENSOR, ANALOG_THRESHOLD_LOW, onDark);

    cplay.lightSensor.setLowThreshold(200);
    cplay.lightSensor.setHighThreshold(950);

    while (1)
    {
        cplay.sleep(1000);
        cplay.serial.printf("LIGHT: %d\n", (int) cplay.lightSensor.getValue());
    }
}

