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

//
// Print details of all events received to the serial port.
// Default settings are 115200 baud, 8N1 over the USB interface.
//
void onButton(DeviceEvent e)
{
    if (e.source == DEVICE_ID_BUTTON_A)
        cplay.serial.printf("BUTTON A: ");

    if (e.source == DEVICE_ID_BUTTON_B)
        cplay.serial.printf("BUTTON B: ");

    if (e.source == DEVICE_ID_BUTTON_C)
        cplay.serial.printf("BUTTON C: ");

    if (e.source == DEVICE_ID_BUTTON_AB)
        cplay.serial.printf("BUTTON A+B: ");

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
    // Register to receive events when any buttons are clicked, including the A+B virtual button (both buttons at once).

    cplay.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_EVT_ANY, onButton);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_EVT_ANY, onButton);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_C, DEVICE_EVT_ANY, onButton);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_AB, DEVICE_EVT_ANY, onButton);

    // We're done, so just enter a power efficient sleep while we wait for an event.
    while (1)
    {
        cplay.sleep(5000);
        cplay.serial.printf("BUTTONA: %d clicks\n", cplay.buttonA.wasPressed());
    }
}

