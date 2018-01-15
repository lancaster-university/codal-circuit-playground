#MicroBit

##Overview

Although the runtime is built from lots of small components, we also provide an easy to use pre-packaged collection of the commonly used components
all in one place. This makes it much easier to start programming your micro:bit in C.

This grouping is provided by a C++ class called `MicroBit`.  The `MicroBit` class has a number of
member variables, that operate as device drivers to control the most commonly used features of the micro:bit.

There is an instance of the `MicroBit` class created as a global variable in all the sample programs, called `uBit`:

>    uBit {<br/>
>    &emsp;&emsp;[.i2c](ubit/i2c.md),<br/>
>    &emsp;&emsp;[.storage](ubit/storage.md),<br/>
>    &emsp;&emsp;[.serial](ubit/serial.md),<br/>
>    &emsp;&emsp;[.MessageBus](ubit/messageBus.md),<br/>
>    &emsp;&emsp;[.buttonA](ubit/button.md),<br/>
>    &emsp;&emsp;[.buttonB](ubit/button.md),<br/>
>    &emsp;&emsp;[.buttonAB](ubit/button.md),<br/>
>    &emsp;&emsp;[.display](ubit/display.md),<br/>
>    &emsp;&emsp;[.accelerometer](ubit/accelerometer.md),<br/>
>    &emsp;&emsp;[.compass](ubit/compass.md),<br/>
>    &emsp;&emsp;[.thermometer](ubit/thermometer.md),<br/>
>    &emsp;&emsp;[.io](ubit/io.md),<br/>
>    &emsp;&emsp;[.radio](ubit/radio.md),<br/>
>    }

You can use dot operator '.' to any of these resources inside uBit to access any of the functions they provide. There is a complete list of the
functions available under the `uBit` menu item in the navigation bar at the top of the page.

For example, if we needed to scroll some text across the display, we simply would write the following:

```cpp
uBit.display.scroll("HELLO!");
```

Similarly, if we wanted to send some text over serial, we could write the following
code:

```cpp
for(int i = 3; i > 0; i--)
{
    uBit.serial.printf("%d...", i);
    uBit.sleep(1000);
}

// or alternatively...
uBit.serial.send("Code!");
```

The runtime also contains a scheduler, which uses lightweight threads (called fibers)
to control the rate of execution.

To place the current fiber into a power efficient <a href="#sleep">sleep</a> write the following:
```cpp
// where X is an integer in milliseconds for the amount of time you would like to sleep for.
uBit.sleep(X);
```

##Message Bus ID

> None

##Message Bus Events

> None

#API
[comment]: <> ({"className":"CircuitPlayground"})
##Constructor
<br/>
####CircuitPlayground()
#####Description
Constructor.  

 Create a representation of a Genuino Zero device, which includes member variables that represent various device drivers used to control aspects of the board.           


____
[comment]: <> ({"end":"CircuitPlayground"})
