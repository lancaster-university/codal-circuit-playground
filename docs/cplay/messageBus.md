#cplay.messageBus

##Overview

##Message Bus ID
| Constant | Value |
| ------------- |-------------|
| DEVICE_ID_MESSAGE_BUS_LISTENER | 1021 |

The message bus will send a `DEVICE_ID_MESSAGE_BUS_LISTENER` event whenever a new listener is added to the message bus.

This event allows other parts of the system to detect when interactions are taking place with a component. This is primarily used as a power management mechanism - allowing on demand activation of hardware when necessary.

##Message Bus Events
| Constant | Value |
| ------------- |-------------|
| Message Bus ID of listener | 1-65535 |


##API
[comment]: <> ({"className":"MessageBus"})
##Constructor
<br/>
####MessageBus()
#####Description
Default constructor.

 Adds itself as a fiber component, and also configures itself to be the default  EventModel  if defaultEventBus is NULL.


##send
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>send</div>( <div style='color:#a71d5d; display:inline-block'>Event</div> evt)
#####Description
Queues the given event to be sent to all registered recipients.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Event</div> evt - The event to send.
#####Example
```cpp
 MessageBus bus;

 // Creates and sends the Event using bus.
 Event evt(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK);

 // Creates the Event, but delays the sending of that event.
 Event evt1(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, CREATE_ONLY);

 bus.send(evt1);

 // This has the same effect!
 evt1.fire()
```
##process
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>process</div>( <div style='color:#a71d5d; display:inline-block'>Event  &</div> evt)
#####Description
Internal function, used to deliver the given event to all relevant recipients. Normally, this is called once an event has been removed from the event queue.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Event  &</div> evt - The event to send.
#####Returns
1 if all matching listeners were processed, 0 if further processing is required.

!!! note
    It is recommended that all external code uses the  send()  function instead of this function, or the constructors provided by  Event .

<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>process</div>( <div style='color:#a71d5d; display:inline-block'>Event  &</div> evt,  <div style='color:#a71d5d; display:inline-block'>bool</div> urgent)
#####Description
Internal function, used to deliver the given event to all relevant recipients. Normally, this is called once an event has been removed from the event queue.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Event  &</div> evt - The event to send.

>  <div style='color:#a71d5d; display:inline-block'>bool</div> urgent - The type of listeners to process (optional). If set to true, only listeners defined as urgent and non-blocking will be processed otherwise, all other (standard) listeners will be processed. Defaults to false.
#####Returns
1 if all matching listeners were processed, 0 if further processing is required.

!!! note
    It is recommended that all external code uses the  send()  function instead of this function, or the constructors provided by  Event .

##elementAt
<br/>
####<div style='color:#a71d5d; display:inline-block'>Listener</div> <div style='color:#795da3; display:inline-block'>elementAt</div>( <div style='color:#a71d5d; display:inline-block'>int</div> n)
#####Description
Returns the  Listener  with the given position in our list.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>int</div> n - The position in the list to return.
#####Returns
the  Listener  at postion n in the list, or NULL if the position is invalid.
##add
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>add</div>( <div style='color:#a71d5d; display:inline-block'>Listener  \*</div> newListener)
#####Description
Add the given  Listener  to the list of event handlers, unconditionally.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Listener  \*</div> newListener
#####Returns
DEVICE_OK if the listener is valid, DEVICE_INVALID_PARAMETER otherwise.
##remove
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>remove</div>( <div style='color:#a71d5d; display:inline-block'>Listener  \*</div> newListener)
#####Description
Remove the given  Listener  from the list of event handlers.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Listener  \*</div> newListener
#####Returns
DEVICE_OK if the listener is valid, DEVICE_INVALID_PARAMETER otherwise.
____
[comment]: <> ({"end":"MessageBus"})
