#Buttons

##Overview


##Message Bus ID
| Constant | Value |
| ------------- |-------------|
| DEVICE_ID_BUTTON_A | 1 |
| DEVICE_ID_BUTTON_B | 2 |

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
[comment]: <> ({"className":"Button"})
##AbstractButton
<br/>
####AbstractButton()
#####Description
Constructor.

 Create a abstract software representation of a button.


##isPressed
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>isPressed</div>()
#####Description
Tests if this  Button  is currently pressed.






#####Returns
1 if this button is pressed, 0 otherwise.
#####Example
```cpp
 if(buttonA.isPressed())
 display.scroll("Pressed!");
```
##wasPressed
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>wasPressed</div>()
#####Description
Determines if this button has been pressed.






#####Returns
the number of time this button has been pressed since the last time  wasPressed()  has been called.
#####Example
```cpp
 if(buttonA.wasPressed())
 display.scroll("Pressed!");
```
##enable
<br/>
####<div style='color:#a71d5d; display:inline-block'>void</div> <div style='color:#795da3; display:inline-block'>enable</div>()
#####Description
Enables this button. Buttons are normally created in an enabled state, but use this funciton to re-enable a previously disabled button.


##disable
<br/>
####<div style='color:#a71d5d; display:inline-block'>void</div> <div style='color:#795da3; display:inline-block'>disable</div>()
#####Description
Disable this button. Buttons are normally created in an enabled state. Use this funciton to disable this button.


____
[comment]: <> ({"end":"Button"})
