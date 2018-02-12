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
#include "TouchSensor.h"

CircuitPlayground cplay;
TouchButton b12(cplay.io.d12, cplay.touchSensor);
TouchButton b6(cplay.io.d6, cplay.touchSensor);

void onButton(DeviceEvent e)
{
    if (e.source == ID_PIN_D6)
        cplay.serial.printf("D6: ");

    if (e.source == ID_PIN_D12)
        cplay.serial.printf("D12: ");

    if (e.value == DEVICE_BUTTON_EVT_DOWN)
        cplay.serial.printf("DOWN");

    if (e.value == DEVICE_BUTTON_EVT_UP)
        cplay.serial.printf("UP");

    if (e.value == DEVICE_BUTTON_EVT_CLICK)
        cplay.serial.printf("CLICK");

    if (e.value == DEVICE_BUTTON_EVT_LONG_CLICK)
        cplay.serial.printf("LONG_CLICK");

    if (e.value == DEVICE_BUTTON_EVT_HOLD)
        cplay.serial.printf("HOLD");

    if (e.value == DEVICE_BUTTON_EVT_DOUBLE_CLICK)
        cplay.serial.printf("DOUBLE_CLICK");

    cplay.serial.printf("\r\n");
}

int main()
{
    cplay.serial.printf("*** TOUCH TEST ***\n");

    cplay.messageBus.listen(ID_PIN_D6, DEVICE_EVT_ANY, onButton);
    cplay.messageBus.listen(ID_PIN_D12, DEVICE_EVT_ANY, onButton);

    while(1)
        cplay.sleep(1000);
}


