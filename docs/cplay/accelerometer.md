#uBit.accelerometer

##Overview

Onboard the micro:bit is an accelerometer, and it is linked to the
[i2c](i2c.md) bus which is used to read data from the accelerometer.

The accelerometer on the micro:bit detects the acceleration (*in milli-g*) in 3 planes: x and y
(*the horizontal planes*), and z (*the vertical plane*).

As well as detecting acceleration, accelerometers can also detect orientation, which
is used in smart phones and tablets to rotate content as you tilt the device. This means
that the micro:bit can infer its own orientation as well!

As well as being used to detect acceleration, accelerometers are also used to detect
the rate of deceleration. A great example of an application of accelerometers are
airbags in modern vehicles, where an accelerometer is used to detect the rapid deceleration
of a vehicle. If rapid deceleration were to occur, the airbags are deployed.

Accelerometers can also be used to detect when an object is in free fall, which is
when only the force gravity is acting upon an object. If you were to throw a ball directly
into the air, free fall would begin as soon as the ball begins its decent after the
acceleration from your throw has subsided.

The micro:bit uses the [MMA8653](../resources/datasheets/MMA8653.pdf).

### Real time updates

When using the standard uBit presentation, the accelerometer is continuously updated
in the background using an idle thread (after it is first used), which is executed
whenever the micro:bit has no other tasks to perform..

If there is no scheduler running, the values are synchronously read on `get[X,Y,Z]()`
calls. Additionally, if you would like to drive accelerometer updates manually `updateSample()`
can be used.

##Message Bus ID

| Constant | Value |
| ------------- |-------------|
| MICROBIT_ID_ACCELEROMETER | 4 |
| MICROBIT_ID_GESTURE | 27 |

##Message Bus Events:

### MICROBIT_ID_ACCELEROMETER

| Constant | Value |
| ------------- |-------------|
| MICROBIT_ACCELEROMETER_EVT_DATA_UPDATE | 1 |

### MICROBIT_ID_GESTURE

| Constant | Value |
| ------------- |-------------|
| MICROBIT_ACCELEROMETER_EVT_TILT_UP | 1 |
| MICROBIT_ACCELEROMETER_EVT_TILT_DOWN | 2 |
| MICROBIT_ACCELEROMETER_EVT_TILT_LEFT | 3 |
| MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT | 4 |
| MICROBIT_ACCELEROMETER_EVT_FACE_UP | 5 |
| MICROBIT_ACCELEROMETER_EVT_FACE_DOWN | 6 |
| MICROBIT_ACCELEROMETER_EVT_FREEFALL | 7 |
| MICROBIT_ACCELEROMETER_EVT_3G | 8 |
| MICROBIT_ACCELEROMETER_EVT_6G | 9 |
| MICROBIT_ACCELEROMETER_EVT_8G | 10 |
| MICROBIT_ACCELEROMETER_EVT_SHAKE | 11 |

##API
[comment]: <> ({"className":"LIS3DH"})
##Constructor
<br/>
####LIS3DH( <div style='color:#a71d5d; display:inline-block'>I2C  &</div> _i2c,  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> _int1,  <div style='color:#a71d5d; display:inline-block'>CoordinateSpace  &</div> coordinateSpace)
#####Description
Constructor. Create a software abstraction of an accelerometer.  

 


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>I2C  &</div> _i2c - an instance of  I2C  used to communicate with the onboard accelerometer.

>  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> _int1

>  <div style='color:#a71d5d; display:inline-block'>CoordinateSpace  &</div> coordinateSpace
#####Example
```cpp
 I2C i2c = I2C(I2C_SDA0, I2C_SCL0); 
 
 Accelerometer accelerometer = Accelerometer(i2c); 
```
<br/>
####LIS3DH( <div style='color:#a71d5d; display:inline-block'>I2C  &</div> _i2c,  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> _int1,  <div style='color:#a71d5d; display:inline-block'>CoordinateSpace  &</div> coordinateSpace,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> address)
#####Description
Constructor. Create a software abstraction of an accelerometer.  

 


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>I2C  &</div> _i2c - an instance of  I2C  used to communicate with the onboard accelerometer.

>  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> _int1

>  <div style='color:#a71d5d; display:inline-block'>CoordinateSpace  &</div> coordinateSpace

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> address - the default  I2C  address of the accelerometer. Defaults to: MMA8653_DEFAULT_ADDR.
#####Example
```cpp
 I2C i2c = I2C(I2C_SDA0, I2C_SCL0); 
 
 Accelerometer accelerometer = Accelerometer(i2c); 
```
<br/>
####LIS3DH( <div style='color:#a71d5d; display:inline-block'>I2C  &</div> _i2c,  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> _int1,  <div style='color:#a71d5d; display:inline-block'>CoordinateSpace  &</div> coordinateSpace,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> address,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id)
#####Description
Constructor. Create a software abstraction of an accelerometer.  

 


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>I2C  &</div> _i2c - an instance of  I2C  used to communicate with the onboard accelerometer.

>  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> _int1

>  <div style='color:#a71d5d; display:inline-block'>CoordinateSpace  &</div> coordinateSpace

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> address - the default  I2C  address of the accelerometer. Defaults to: MMA8653_DEFAULT_ADDR.

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id - the unique  EventModel  id of this component. Defaults to: DEVICE_ID_ACCELEROMETER
#####Example
```cpp
 I2C i2c = I2C(I2C_SDA0, I2C_SCL0); 
 
 Accelerometer accelerometer = Accelerometer(i2c); 
```
##setPeriod
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>setPeriod</div>( <div style='color:#a71d5d; display:inline-block'>int</div> period)
#####Description
Attempts to set the sample rate of the accelerometer to the specified value (in ms).  

 

 


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>int</div> period - the requested time between samples, in milliseconds.
#####Returns
DEVICE_OK on success, DEVICE_I2C_ERROR is the request fails.
#####Example
```cpp
 // sample rate is now 20 ms. 
 accelerometer.setPeriod(20); 
```

!!! note
    The requested rate may not be possible on the hardware. In this case, the nearest lower rate is chosen. 

##getPeriod
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>getPeriod</div>()
#####Description
Reads the currently configured sample rate of the accelerometer.  

 


#####Returns
The time between samples, in milliseconds. 
##setRange
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>setRange</div>( <div style='color:#a71d5d; display:inline-block'>int</div> range)
#####Description
Attempts to set the sample range of the accelerometer to the specified value (in g).  

 

 


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>int</div> range - The requested sample range of samples, in g.
#####Returns
DEVICE_OK on success, DEVICE_I2C_ERROR is the request fails.
#####Example
```cpp
 // the sample range of the accelerometer is now 8G. 
 accelerometer.setRange(8); 
```

!!! note
    The requested range may not be possible on the hardware. In this case, the nearest lower range is chosen. 

##getRange
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>getRange</div>()
#####Description
Reads the currently configured sample range of the accelerometer.  

 


#####Returns
The sample range, in g. 
##whoAmI
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>whoAmI</div>()
#####Description
Attempts to read the 8 bit ID from the accelerometer, this can be used for validation purposes.  

 


#####Returns
the 8 bit ID returned by the accelerometer, or DEVICE_I2C_ERROR if the request fails.
#####Example
```cpp
 accelerometer.whoAmI(); 
```
##getSample
<br/>
####<div style='color:#a71d5d; display:inline-block'>Sample3D</div> <div style='color:#795da3; display:inline-block'>getSample</div>()
#####Description
Reads the accelerometer data from the latest update retrieved from the accelerometer. Data is provided in ENU format, relative to the device package (and makes no attempt to align axes to the device).  

 


#####Returns
The force measured in each axis, in milli-g. 
##configure
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>configure</div>()
#####Description
Configures the accelerometer for G range and sample rate defined in this object. The nearest values are chosen to those defined that are supported by the hardware. The instance variables are then updated to reflect reality.  

 


#####Returns
DEVICE_OK on success, DEVICE_I2C_ERROR if the accelerometer could not be configured. 
##updateSample
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>updateSample</div>()
#####Description
Reads the acceleration data from the accelerometer, and stores it in our buffer. This only happens if the accelerometer indicates that it has new data via int1.  

 On first use, this member function will attempt to add this component to the list of fiber components in order to constantly update the values stored by this object.  

 This technique is called lazy instantiation, and it means that we do not obtain the overhead from non-chalantly adding this component to fiber components.  

 


#####Returns
DEVICE_OK on success, DEVICE_I2C_ERROR if the read request fails. 
##requestUpdate
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>requestUpdate</div>()
#####Description
Poll to see if new data is available from the hardware. If so, update it. n.b. it is not necessary to explicitly call this funciton to update data (it normally happens in the background when the scheduler is idle), but a check is performed if the user explicitly requests up to date data.  

 


#####Returns
DEVICE_OK on success, DEVICE_I2C_ERROR if the update fails.

!!! note
    This method should be overidden by the hardware driver to implement the requested changes in hardware. 

____
[comment]: <> ({"end":"LIS3DH"})
