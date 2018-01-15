#CircuitPlayground

##Overview

Although the runtime is built from lots of small components, we also provide an easy to use pre-packaged collection of the commonly used components
all in one place. This makes it much easier to start programming your micro:bit in C.

This grouping is provided by a C++ class called `CircuitPlayground`.  The `CircuitPlayground` class has a number of
member variables, that operate as device drivers to control the most commonly used features of the micro:bit.

There is an instance of the `CircuitPlayground` class created as a global variable in all the sample programs, called `cplay`:

>    cplay {<br/>
>    &emsp;&emsp;[.i2c](cplay/i2c.md),<br/>
>    &emsp;&emsp;[.serial](cplay/serial.md),<br/>
>    &emsp;&emsp;[.MessageBus](cplay/messageBus.md),<br/>
>    &emsp;&emsp;[.buttonA](cplay/button.md),<br/>
>    &emsp;&emsp;[.buttonB](cplay/button.md),<br/>
>    &emsp;&emsp;[.buttonAB](cplay/button.md),<br/>
>    &emsp;&emsp;[.accelerometer](cplay/accelerometer.md),<br/>
>    &emsp;&emsp;[.thermometer](cplay/thermometer.md),<br/>
>    &emsp;&emsp;[.io](cplay/io.md),<br/>
>    }

You can use dot operator '.' to any of these resources inside cplay to access any of the functions they provide. There is a complete list of the
functions available under the `cplay` menu item in the navigation bar at the top of the page.

For example, if we needed to scroll some text across the display, we simply would write the following:

```cpp
cplay.display.scroll("HELLO!");
```

Similarly, if we wanted to send some text over serial, we could write the following
code:

```cpp
for(int i = 3; i > 0; i--)
{
    cplay.serial.printf("%d...", i);
    cplay.sleep(1000);
}

// or alternatively...
cplay.serial.send("Code!");
```

The runtime also contains a scheduler, which uses lightweight threads (called fibers)
to control the rate of execution.

To place the current fiber into a power efficient <a href="#sleep">sleep</a> write the following:
```cpp
// where X is an integer in milliseconds for the amount of time you would like to sleep for.
cplay.sleep(X);
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
