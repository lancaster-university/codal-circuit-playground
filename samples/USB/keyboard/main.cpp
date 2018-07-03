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
#include "USB_HID_Keys.h"
#include "HIDKeyboard.h"

CircuitPlayground cplay;

CodalUSB usb;
USBHIDKeyboard hid;

static const char *string_descriptors[] = {
    "Example Corp.", "PXT Device", "42424242",
};

void typeLetters(Event)
{
    hid.type("Hello!");
}

void mediaKey(Event)
{
    hid.press(VolumeUp);
    cplay.sleep(1000);
    hid.press(Home);
    cplay.sleep(1000);
    hid.press(F1Key);
}

static const Key seq_hello[] = {
    { .reg = KEYMAP_KEY_DOWN | KEY_H },
    { .reg = KEYMAP_KEY_UP | KEY_H },

    { .reg = KEYMAP_KEY_DOWN | KEY_E },
    { .reg = KEYMAP_KEY_UP | KEY_E },

    { .reg = KEYMAP_KEY_DOWN | KEY_L },
    { .reg = KEYMAP_KEY_UP | KEY_L },

    { .reg = KEYMAP_KEY_DOWN | KEY_L },
    { .reg = KEYMAP_KEY_UP | KEY_L },

    { .reg = KEYMAP_KEY_DOWN | KEY_O },
    { .reg = KEYMAP_KEY_UP | KEY_O }
};

const KeySequence keymap_hello_world[] = {
	KEYMAP_REGISTER(seq_hello)
};

void writeSequence(Event)
{
    hid.type(keymap_hello_world);
}

int main()
{
    usb.stringDescriptors = string_descriptors;
    usb.add(hid);
    usb.start();

    //we need a bit of a delay for USB
    cplay.sleep(500);

    cplay.messageBus.listen(DEVICE_ID_BUTTON_A,DEVICE_BUTTON_EVT_CLICK,typeLetters);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_B,DEVICE_BUTTON_EVT_CLICK,mediaKey);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_AB,DEVICE_BUTTON_EVT_CLICK,writeSequence);

    release_fiber();
}