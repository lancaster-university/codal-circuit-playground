# Advanced Features of the Runtime

Under the surface, the micro:bit runtime is a highly configurable, modular and component based piece of software.

The `uBit` object is provided as a collection of the commonly used components, all gathered together in one place
to make it easier for novice users to access the functionality of the device. However, there is no obligation to
use the `uBit` abstraction. More advanced users may prefer to create and use only the parts of the runtime they
need.

This provides more control and often frees up more memory resource for the application program - but does so
at the expense of the user taking more responsibility and additional complexity in their programs.

## Using Components Directly

Taking advantage of the modular structure of the micro:bit runtime is fairly straightforward.

 - Firstly, create a program that does **not** create or initialise a uBit object.
 - Include `MicroBit.h` (or if you prefer, just the header files of the components you want to use). Including `MicroBit.h` is however, simpler.
 - Instead, create C++ object instances of the classes that you want to use **as global variables** in your program. Create as many components as you need. You are free to use any of the constructors in this documentation.
 - Call functions on those instances to elicit the behaviour you need, using the name of your object instances instead of `uBit.*`

For example, if you wanted to create a program that just used the LED matrix display driver, you might write a program like this:

```cpp
#include "MicroBit.h"

MicroBitDisplay display;

int main()
{
    while(1)
        display.scroll(":)");
}
```

If you need other components, add them to your program in the same way.

If a component has a dependency on another component (e.g. in the example below, the accelerometer is dependent on an I2C bus), then this will be requested as a mandatory parameter in the constructor.

See the 'Constructor' section of the each components' API documentation for details and examples.
```cpp
#include "MicroBit.h"

MicroBitI2C i2c = MicroBitI2C(I2C_SDA0, I2C_SCL0);
MicroBitAccelerometer accelerometer = MicroBitAccelerometer(i2c);
MicroBitDisplay display;

int main()
{
    while(1)
        display.scroll(accelerometer.getX());
}
```

!!! warning
    micro:bit runtime components should **always** be brought up as global variables. They should **not** be created as local variables - either in your main method or anywhere else. The reason for this is the the runtime is a multi-threaded environment, and any variables created in stack memory (like local variables) may be paged out by the scheduler, and result in instability if they utilise interrupts or are accessed by other threads. So... don't do it!


## System Components

There are also system components that provide background services. Without the `uBit` object, these will not be created by default.  Examples include the fiber scheduler, message bus and heap allocator.

You are not required to initialise these components, but you should do so if you want to benefit from the functionality they provide. The following section describe how to do this.

## Initialising the Message Bus
The [`MicroBitMessageBus`](ubit/messageBus.md) allows events to be created and delivered to applications.  So if a [`MicroBitMessageBus`](ubit/messageBus.md) is not created, then all events in the micro:bit runtime will be quietly ignored.

To enable this functionality, simply create an instance of the [`MicroBitMessageBus`](ubit/messageBus.md) class. From that point onward in your program, you can raise and listen for events as described in the [`MicroBitMessageBus`](ubit/messageBus.md) documentation.

```cpp
#include "MicroBit.h"

MicroBitMessageBus bus;
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitDisplay display;

void onPressed(MicroBitEvent e)
{
    display.print("S");    
}

int main()
{
    bus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onPressed);

    while(1)
    {
    }
}
```

!!! warning
    Running a MessageBus without the Fiber Scheduler will result in all event handlers being registered as MESSAGE_BUS_LISTENER_IMMEDIATE (see [`MicroBitMessageBus`](ubit/messageBus.md) for details). This means that your event handler will be executed in the context of the code that raised the event. This may include interrupt context, which may not be safe for all operations. It is recommend that you always run the MessageBus with the Fiber Scheduler in order to allow the event to be decoupled from interrupt context.

## Initialising the Fiber Scheduler

Often when using asynchronous events, it is also useful to run the fiber scheduler. Without a scheduler in operation, all event handlers (such as the one above) will be executed with the threading mode `MESSAGE_BUS_LISTENER_IMMEDIATE`, as
described on the [`MicroBitMessageBus`](ubit/messageBus.md) documentation.

Also, it is not really possible to transparently enter a power efficient sleep - as illustrated in the busy loop in the above example.

Initialising the fiber scheduler is simple, and is demonstrated in the following example.

From the moment the fiber scheduler is initialised, it is then possible to block the processor in a power efficient way and to operate threaded event handlers:

```c++
#include "MicroBit.h"

MicroBitMessageBus bus;
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitDisplay display;

void onPressed(MicroBitEvent e)
{
    display.print("S");    
}

int main()
{
    scheduler_init(bus);

    bus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onPressed);

    while(1)
        fiber_sleep(1000);
}
```

!!!note
    Function calls to `uBit.sleep()` must be replaced with the direct, equivalent calls to the scheduler using `fiber_sleep()`.

## Initialising the Heap Allocator

The micro:bit runtime provides an optional, heap memory allocator. This is primarily to permit the use of **multiple** regions of memory to be used as heap memory space for your variables.

The `uBit` initialisation function will automatically release any memory unused by the Bluetooth stack for general purpose use in this fashion (this typically provides an additional 1K of SRAM under Bluetooth enabled builds, and another 8K if Bluetooth is disabled).

Should you wish to also reclaim memory in this way, you can do so as follows:
```c++
#include "MicroBit.h"

int main()
{
    microbit_create_heap(MICROBIT_SD_GATT_TABLE_START + MICROBIT_SD_GATT_TABLE_SIZE, MICROBIT_SD_LIMIT);
}
```

## Compile Time Configuration Options
In addition to the flexibility to initialise only the components that you need, the runtime also provides a central, compile time configuration file called `MicroBitConfig.h`.

You can use this to reconfigure the default behaviour of the runtime.

The default settings will provide a stable working environment, but advanced users may want to further tailor the behaviour.

To tailor the behaviour, simply edit the `MicroBitConfig.h` file to change the settings, and then perform a clean rebuild.

###Compile Time Options with MicroBitConfig.h

The following options are configurable at compile time through `MicroBitConfig.h`:

| Configuration option | Brief Description |
| ------------- |-------------|
| `MICROBIT_HEAP_ALLOCATOR` | Enables or disables the MicroBitHeapAllocator for `uBit` based builds. |
| `MICROBIT_HEAP_BLOCK_SIZE` | The Block size used by the heap allocator in bytes. |
| `MICROBIT_NESTED_HEAP_SIZE` | The proportion of SRAM available on the mbed heap to reserve for the micro:bit heap. |
| `MICROBIT_HEAP_REUSE_SD` | If set to '1', any unused areas of the Soft Device GATT table will be automatically reused as heap memory. |
| `MICROBIT_SD_GATT_TABLE_SIZE` | The amount of memory (bytes) to dedicate to the SoftDevice GATT table. |
| `SYSTEM_TICK_PERIOD_MS` | The default scheduling quantum |
| `EVENT_LISTENER_DEFAUT_FLAGS` | The default threading mode used when a `MicroBitMessageBus` listener is created. |
| `MESSAGE_BUS_LISTENER_MAX_QUEUE_DEPTH` | Maximum event queue depth. If a queue exceeds this depth, further events will be dropped. |
| `MICROBIT_SYSTEM_COMPONENTS` | The maximum size of the interrupt callback list. |
| `MICROBIT_IDLE_COMPONENTS` | The maximum size of the idle callback list. |
| `MICROBIT_BLE_ENABLED` | Enable/Disable Bluetooth during normal operation. If disabled, no Bluetooth communication is possible, but radio functionality is made possible, and an additional 8K of SRAM is released|
| `MICROBIT_BLE_PAIRING_MODE` | Enable/Disable Bluetooth pairing mode with A+B / reset at power up|
| `MICROBIT_BLE_PRIVATE_ADDRESSES` | Enable/Disable the use of private resolvable addresses. **This is known to be a feature that suffers compatibility issues with many Bluetooth central devices.** |
| `MICROBIT_BLE_OPEN` | Enable/Disable Bluetooth security entirely. Open Bluetooth links are not secure, but are highly useful during the development of Bluetooth services|
| `MICROBIT_BLE_SECURITY_LEVEL` | Define the default, global Bluetooth security requirements for MicroBit Bluetooth services|
| `MICROBIT_BLE_WHITELIST` | Enable/Disable the use of Bluetooth whitelisting.|
| `MICROBIT_BLE_ADVERTISING_TIMEOUT` | Define the period of time for which the Bluetooth stack will advertise (seconds).|
| `MICROBIT_BLE_DEFAULT_TX_POWER` | Defines default power level of the Bluetooth radio transmitter.|
| `MICROBIT_BLE_DFU_SERVICE` | Enable/Disable Bluetooth Service: MicroBitDFU. This allows over the air programming during normal operation.|
| `MICROBIT_BLE_EVENT_SERVICE` | Enable/Disable Bluetooth Service: MicroBitEventService. This allows routing of events from the micro:bit message bus over Bluetooth.|
| `MICROBIT_BLE_DEVICE_INFORMATION_SERVICE` | Enable/Disable Bluetooth Service: MicroBitDeviceInformationService. This enables the standard Bluetooth device information service.|
| `MICROBIT_BLE_EDDYSTONE_URL` | Enable/Disable Eddystone URL support. Enabling this enables you to broadcast a physical web url from the microbit |
| `USE_ACCEL_LSB` | Enable 10 bit sampling on the accelerometer. By default, a more efficient 8 bit sampling if used.|
| `MICROBIT_DISPLAY_TYPE` | Selects the default matrix configuration for the display driver.|
| `MICROBIT_DISPLAY_MINIMUM_BRIGHTNESS` | Selects the minimum permissible brightness level for the device.|
| `MICROBIT_DISPLAY_MAXIMUM_BRIGHTNESS` | Selects the maximum permissible brightness level for the device.|
| `MICROBIT_DISPLAY_DEFAULT_BRIGHTNESS` | Selects the default brightness level for the device.|
| `MICROBIT_DEFAULT_SCROLL_SPEED` | Selects the time taken to scroll a single pixel, in milliseconds.|
| `MICROBIT_DEFAULT_SCROLL_STRIDE` | Selects the number of pixels a scroll will move in each quantum.|
| `MICROBIT_DEFAULT_PRINT_SPEED` | Selects the time each character will be shown on the display during print operations, in milliseconds.|
| `MICROBIT_DEFAULT_SERIAL_MODE` | Configures the default serial mode used by serial read and send calls.|
| `MICROBIT_DEFAULT_PULLMODE` | Define the default mode in which the digital input pins are configured. Valid options are PullDown, PullUp and PullNone.|
| `MICROBIT_PANIC_HEAP_FULL` | Enable this to invoke a panic on out of memory conditions.|
| `MICROBIT_DBG` | Enable this to route debug messages through the USB serial interface.|
| `MICROBIT_HEAP_DBG` | Enable this to receive detailed diagnostic messages from the heap allocator via the USB serial interface.|
| `MICROBIT_DAL_VERSION` | Define the default version information of the runtime.|

There are also some constants that define the geometry of the micro:bit memory

!!! warning
    Only change these if you really know what you are doing!

| Configuration option | Brief Description |
| ------------- |-------------|
| `MICROBIT_SRAM_BASE` |  The start address of usable RAM memory. |
| `MICROBIT_SRAM_END` |  The end address of usable RAM memory. |
| `MICROBIT_SD_LIMIT` |  The end address of RAM memory reserved for Soft Device (Nordic's Bluetooth stack). |
| `MICROBIT_SD_GATT_TABLE_START` |  The start address of the Bluetooth GATT table in RAM. |
| `CORTEX_M0_STACK_BASE` | The memory address of the top of the system stack. |
| `MICROBIT_STACK_SIZE` | Amount of memory reserved for the stack (in bytes). |
| `MICROBIT_HEAP_END` | The end address of the mbed heap space |

### Compile Time Options with Yotta

Rather than edit the `MicroBitConfig.h` file to change the default behaviour of the runtime, if you are using
`yotta`, you can also provide a `config.json` in your project.

Here's a `config.json`, using all available configuration options, that matches the default values specified in `MicroBitConfig.h`:

```json
{
    "microbit-dal":{
        "bluetooth":{
            "enabled": 1,
            "pairing_mode": 1,
            "private_addressing": 0,
            "open": 0,
            "whitelist": 1,
            "advertising_timeout": 0,
            "tx_power": 0,
            "dfu_service": 1,
            "event_service": 1,
            "device_info_service": 1,
            "eddystone_url": 0
        },
        "reuse_sd": 1,
        "default_pullmode":"PullDown",
        "gatt_table_size": "0x300",
        "heap_allocator": 1,
        "nested_heap_proportion": 0.75,
        "system_tick_period": 6,
        "system_components": 10,
        "idle_components": 6,
        "use_accel_lsb": 0,
        "min_display_brightness": 1,
        "max_display_brightness": 255,
        "display_scroll_speed": 120,
        "display_scroll_stride": -1,
        "display_print_speed": 400,
        "panic_on_heap_full": 1,
        "debug": 0,
        "heap_debug": 0,
        "stack_size":2048,
        "sram_base":"0x20000008",
        "sram_end":"0x20004000",
        "sd_limit":"0x20002000",
        "gatt_table_start":"0x20001900"
    }
}
```

It should be noted that **all** of the above options are optional, and will revert to their default values
if not specified. This means that we can also provide a subset of these options, to configure specific
parts of the runtime:

```json
{
    "microbit-dal":{
        "bluetooth":{
            "open": 1
        },
        "debug":1
    }
}
```

Additionally, the options provided through `config.json` intuitively map onto the `#defines`
listed in `MicroBitConfig.h`

An example of `config.json` in operation is available at the [microbit-samples](https://github.com/lancaster-university/microbit-samples) GitHub repository.
