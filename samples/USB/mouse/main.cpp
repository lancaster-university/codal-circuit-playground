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

#include "CircuitPlayground.h"
#include "HIDMouse.h"

CircuitPlayground cplay;

CodalUSB usb;
USBHIDMouse hid;

static const char *string_descriptors[] = {
    "Example Corp.", "PXT Device", "42424242",
};

void moveXY(){
    //move x direction
    hid.move(50, 0);
    cplay.sleep(500); //wait
    hid.move(-50, 0);
    cplay.sleep(500); //wait

    //move y direction
    hid.move(0, 50);
    cplay.sleep(500); //wait
    hid.move(0, -50);
    cplay.sleep(500); //wait
}

void clicks(){
    hid.buttonDown(HID_MOUSE_LEFT);
    cplay.sleep(500); //wait
    hid.buttonUp(HID_MOUSE_LEFT);
    cplay.sleep(500); //wait

    hid.buttonDown(HID_MOUSE_MIDDLE);
    cplay.sleep(500); //wait
    hid.buttonUp(HID_MOUSE_MIDDLE);
    cplay.sleep(500); //wait

    hid.buttonDown(HID_MOUSE_RIGHT);
    cplay.sleep(500); //wait
    hid.buttonUp(HID_MOUSE_RIGHT);
    cplay.sleep(500); //wait
}

void wheel(){
    hid.moveWheel(50);
    cplay.sleep(500); //wait
    hid.moveWheel(-50);
    cplay.sleep(500); //wait
}

int main()
{
    usb.stringDescriptors = string_descriptors;
    usb.add(hid);
    usb.start();

    //we need a bit of a delay for USB
    cplay.sleep(500);

    while(1){
        moveXY();

        clicks();

        wheel();
    }
}