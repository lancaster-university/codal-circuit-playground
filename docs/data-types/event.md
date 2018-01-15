#MicroBitEvent

##Overview

Computer programs execute sequentially - one line after another, following the logic of the program you have written.
Sometimes though, we want to be able to determine *when* something has happened, and write some code to decide what should
happen in that case. For example, maybe you want to know when a button has been pressed, when your micro:bit has been shaken,
or when some data has been sent to you over the micro:bit radio. For these sorts of cases, we create a `MicroBitEvent`.


## Creating Events
Many components will raise events when interesting things occur. For example, ['Accelerometer'](../cplay/accelerometer.md) will raise events to indicate that the
micro:bit has be been shaken, or is in freefall and ['Button'](../cplay/button.md) will send events on a range of button up, down, click and hold events.
Programmers are also free to send their own events whenever they feel it would be useful. `Event`s are *very* simple, and consist of
only two numbers:

  - `source` - A number identifying the component that created the event.
  - `value` - A number unique to the source that identifies the event.

The documentation for each component defines its event source, and all the events it may generate, and also gives a name to these
event values. For example, take a look at the [button documentation](../cplay/button.md) to see that the source DEVICE_ID_BUTTON_A has the value '1',
and an event DEVICE_BUTTON_EVT_CLICK with the value '3' is generated when a button is clicked.

Creating an event is easy - just create a MicroBitEvent with the `source` and `value` you need, and the runtime takes care of the rest:

```cpp
MicroBitEvent(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK);
```

Feel free to create your own events lke this too. Just try to avoid using any source ID that is already used by the runtime! :-)
See the [messageBus](../cplay/messageBus.md) page for a complete table of the reserved source IDs.


## Detecting Events
The micro:bit runtime has a component called the [`MessageBus`](../cplay/messageBus.md), and its job is remember which events your program is interested in, and
to deliver `Event`s to your program as they occur.

To find out when an event happens, you need to create a function in your program,
then tell the message bus which event you want to attach this function to. This is known as writing an **event handler**.

You write an event handler through the `MessageBus` [listen](../cplay/messageBus.md) function.


#API
[comment]: <> ({"className":"Event"})
##Constructor
<br/>
####Event( <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value)
#####Description
Constructor.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value - A component specific code indicating the cause of the event.
#####Example
```cpp
 // Create and launch an event using the default configuration
 Event evt(id,DEVICE_BUTTON_EVT_CLICK);

 // Create an event only, do not fire onto an EventModel.
 Event evt(id,DEVICE_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
```
<br/>
####Event( <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value,  <div style='color:#a71d5d; display:inline-block'>EventLaunchMode</div> mode)
#####Description
Constructor.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value - A component specific code indicating the cause of the event.

>  <div style='color:#a71d5d; display:inline-block'>EventLaunchMode</div> mode - Optional definition of how the event should be processed after construction (if at all): CREATE_ONLY:  Event  is initialised, and no further processing takes place. CREATE_AND_FIRE:  Event  is initialised, and its event handlers are immediately fired (not suitable for use in interrupts!).
#####Example
```cpp
 // Create and launch an event using the default configuration
 Event evt(id,DEVICE_BUTTON_EVT_CLICK);

 // Create an event only, do not fire onto an EventModel.
 Event evt(id,DEVICE_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
```
<br/>
####Event( <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value,  <div style='color:#a71d5d; display:inline-block'>CODAL_TIMESTAMP</div> currentTimeUs)
#####Description
Constructor.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value - A component specific code indicating the cause of the event.

>  <div style='color:#a71d5d; display:inline-block'>CODAL_TIMESTAMP</div> currentTimeUs - The current time in microseconds.
#####Example
```cpp
 // Create and launch an event using the default configuration
 Event evt(id,DEVICE_BUTTON_EVT_CLICK);

 // Create an event only, do not fire onto an EventModel.
 Event evt(id,DEVICE_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
```
<br/>
####Event( <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value,  <div style='color:#a71d5d; display:inline-block'>CODAL_TIMESTAMP</div> currentTimeUs,  <div style='color:#a71d5d; display:inline-block'>EventLaunchMode</div> mode)
#####Description
Constructor.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> source

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> value - A component specific code indicating the cause of the event.

>  <div style='color:#a71d5d; display:inline-block'>CODAL_TIMESTAMP</div> currentTimeUs - The current time in microseconds.

>  <div style='color:#a71d5d; display:inline-block'>EventLaunchMode</div> mode - Optional definition of how the event should be processed after construction (if at all): CREATE_ONLY:  Event  is initialised, and no further processing takes place. CREATE_AND_FIRE:  Event  is initialised, and its event handlers are immediately fired (not suitable for use in interrupts!).
#####Example
```cpp
 // Create and launch an event using the default configuration
 Event evt(id,DEVICE_BUTTON_EVT_CLICK);

 // Create an event only, do not fire onto an EventModel.
 Event evt(id,DEVICE_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
```
<br/>
####Event()
#####Description
Default constructor - initialises all values, and sets timestamp to the current time.


##fire
<br/>
####<div style='color:#a71d5d; display:inline-block'>void</div> <div style='color:#795da3; display:inline-block'>fire</div>()
#####Description
Fires this  Event  onto the Default  EventModel , or a custom one!


____
[comment]: <> ({"end":"Event"})
