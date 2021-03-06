#uBit.buttonAB

##Overview


##Message Bus ID
| Constant | Value |
| ------------- |-------------|
| DEVICE_ID_BUTTON_AB | 26 |

##Message Bus Events

| Constant | Value |
| ------------- |-------------|
| DEVICE_BUTTON_EVT_DOWN | 1 |
| DEVICE_BUTTON_EVT_UP | 2 |
| DEVICE_BUTTON_EVT_CLICK | 3 |
| DEVICE_BUTTON_EVT_LONG_CLICK | 4 |
| DEVICE_BUTTON_EVT_HOLD | 5 |
| DEVICE_BUTTON_EVT_DOUBLE_CLICK | 6 |

##API
[comment]: <> ({"className":"MultiButton"})
##Constructor
<br/>
####MultiButton( <div style='color:#a71d5d; display:inline-block'>uint16_t</div> button1,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> button2,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id)
#####Description
Constructor.

 Create a representation of a virtual button, that generates events based upon the combination of two given buttons.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> button1 - the unique ID of the first button to watch.

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> button2 - the unique ID of the second button to watch.

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id - the unique  EventModel  id of this  MultiButton  instance.
#####Example
```cpp
 multiButton(DEVICE_ID_BUTTON_A, DEVICE_ID_BUTTON_B, DEVICE_ID_BUTTON_AB);
```
##isPressed
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>isPressed</div>()
#####Description
Tests if this  MultiButton  instance is virtually pressed.




#####Returns
1 if both physical buttons are pressed simultaneously.
#####Example
```cpp
 if(buttonAB.isPressed())
 display.scroll("Pressed!");
```
##setEventConfiguration
<br/>
####<div style='color:#a71d5d; display:inline-block'>void</div> <div style='color:#795da3; display:inline-block'>setEventConfiguration</div>( <div style='color:#a71d5d; display:inline-block'>ButtonEventConfiguration</div> config)
#####Description
Changes the event configuration of this button to the given ButtonEventConfiguration. All subsequent events generated by this button will then be informed by this configuration.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>ButtonEventConfiguration</div> config - The new configuration for this button. Legal values are DEVICE_BUTTON_ALL_EVENTS or DEVICE_BUTTON_SIMPLE_EVENTS.
#####Example
```cpp
 // Configure a button to generate all possible events.
 buttonAB.setEventConfiguration(DEVICE_BUTTON_ALL_EVENTS);

 // Configure a button to suppress DEVICE_BUTTON_EVT_CLICK and DEVICE_BUTTON_EVT_LONG_CLICK events.
 buttonAB.setEventConfiguration(DEVICE_BUTTON_SIMPLE_EVENTS);
```
____
[comment]: <> ({"end":"MultiButton"})
