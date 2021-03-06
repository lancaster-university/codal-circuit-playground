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

void onShake(DeviceEvent)
{
    cplay.serial.printf("*** SHAKE ***\n");
}

int main()
{
    cplay.sleep(100);

    SERIAL_DEBUG->printf("DEBUG ON\n");

    cplay.messageBus.listen(DEVICE_ID_GESTURE, ACCELEROMETER_EVT_SHAKE, onShake);

    while (1)
    {
        cplay.sleep(500);
        cplay.serial.printf("ACC: [X:%d Y:%d Z:%d]\r\n", cplay.accelerometer.getX(), cplay.accelerometer.getY(), cplay.accelerometer.getZ());
    }
}

