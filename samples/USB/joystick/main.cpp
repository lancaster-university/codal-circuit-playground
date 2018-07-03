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
#include "HIDJoystick.h"

CircuitPlayground cplay;

CodalUSB usb;
USBHIDJoystick hid;

static const char *string_descriptors[] = {
    "Example Corp.", "PXT Device", "42424242",
};

void throttle() {
    //both throttles
    for(int i=0; i<2; i++){

        //increase throttle
        for(int j=0; j<31; j++){
            hid.setThrottle(i, j);
            cplay.sleep(50);
        }

        //move throttle back down
        for(int j=31; j>0; j--){
            hid.setThrottle(i, j);
            cplay.sleep(50);
        }

    }
}

void buttons() {
  //set buttons
  for(int i=0; i<16; i++){
    hid.buttonDown(i);
    cplay.sleep(100);
  }

  //clear buttons
  for(int i=0; i<16; i++){
    hid.buttonUp(i);
    cplay.sleep(100);
  }
}

void sticks() {
  //both joysticks
  for(int i=0; i<2; i++){

        //move x axis up
        for(int j=0; j<127; j+=8){
            hid.move(i, j, 0);
            cplay.sleep(50);
        }

        //move x axis back down
        for(int j=127; j>0; j-=8){
            hid.move(i, j, 0);
            cplay.sleep(50);
        }

        //move y axis up
        for(int j=0; j<127; j+=8){
            hid.move(i, 0, j);
            cplay.sleep(50);
        }

        //move y axis back down
        for(int j=127; j>0; j-=8){
            hid.move(i, 0, j);
            cplay.sleep(50);
        }

    }
}

int main()
{
    usb.stringDescriptors = string_descriptors;
    usb.add(hid);
    usb.start();

    //we need a bit of a delay for USB
    cplay.sleep(500);

    while(1){
        throttle();

        buttons();

        sticks();
    }
}