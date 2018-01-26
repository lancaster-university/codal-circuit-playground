#Introduction

The CODAL runtime provides an easy to use environment for programming the CircuitPlayground Express
in the C/C++ language, written by Lancaster University. It contains device drivers for all the hardware capabilities of the micro:bit,
and also a suite of runtime mechanisms to make programming the micro:bit easier and more flexible. These
range from control of the LED matrix display to peer-to-peer radio communication and secure
Bluetooth Low Energy services.

In addition to supporting development in C/C++, the runtime is also designed specifically to support
higher level languages provided by our partners that target the micro:bit. It is currently used as a support library for [Microsoft MakeCode](https://makecode.com)

On these pages you will find guidance on how to start using the runtime in C/C++, summaries of all the
components that make up the system and a full set of API documentation (the functions you can use to control the micro:bit).

Just to show how easy it is to get started, view a <a href="#next-steps">sample program</a>.

#Getting Started

Developing with the CODAL runtime is simple, and there are multiple ways to create programs for your device.

## Next Steps

After you've chosen your development environment, the next step is obvious: **PROGRAM**!

Here is some sample code to get you started:

```cpp
#include "CircuitPlayground.h"

CircuitPlayground cplay;

int main()
{
    while(1)
    {
        cplay.io.led.setDigitalValue(1);
        cplay.sleep(500);
        cplay.io.led.setDigitalValue(1);
        cplay.sleep(500);
    }
    release_fiber();
}
```

### What is cplay?

uBit is an instance of the [CircuitPlayground](cplay.md) class which provides a really simple way to interact
with the various components on the micro:bit itself.

This simplicity can be seen with this line of code:

```cpp
cplay.io.led.setDigitalValue(1);
```

This line sets the LED indicator on the device.


### What is a fiber and why do we release it?

Fibers are lightweight threads used by the runtime to perform operations asynchronously.

The function call `release_fiber();` is recommended at the end of main to release the main fiber, and enter
the scheduler indefinitely as you may have other fibers running elsewhere in the code.
It also means that the processor will enter a power efficient sleep if there are
no other processes running.

If this line is omitted, your program will cease all execution.
