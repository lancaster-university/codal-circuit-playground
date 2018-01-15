#uBit.thermometer

##Overview

MicroBitThermometer provides access to the surface temperature of the nrf51822.
The temperature reading therefore is not representative of the ambient temperature,
but rather the temperature relative to the surface temperature of the chip.

However, we can make it representative of the ambient temperature in software
through "calibrating" the thermometer.

Calibration is very simple, and is calculated by giving the current temperature
to the `setCalibration()` member function. From the temperature, an offset is
calculated, and is subsequently used to offset future temperature readings.


### Real time updates

When using the standard uBit presentation, the thermometer is continuously updated
in the background using an idle thread (after it is first used), which is executed
whenever the micro:bit has no other tasks to perform.

If there is no scheduler running, the values are synchronously read on `getTemperature()`
calls. Additionally, if you would like to drive thermometer updates manually `updateSample()`
can be used.

##Message Bus ID

| Constant | Value |
| ------------- |-------------|
| MICROBIT_ID_THERMOMETER | 28 |

##Message Bus Events

| Constant | Value |
| ------------- |-------------|
| MICROBIT_THERMOMETER_EVT_UPDATE | 1 |

##API
[comment]: <> ({"className":"LinearAnalogSensor"})
##Constructor
<br/>
####LinearAnalogSensor( <div style='color:#a71d5d; display:inline-block'>Pin  &</div> pin,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleFloor,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleCeiling)
#####Description
Constructor.  

 Creates a  LinearAnalogSensor .  

   
 
 pin 
 
 
 The pin on which to sense   
 
 
 
 id 
 
 
 The ID of this compoenent e.g. DEVICE_ID_THERMOMETER   
 
 
 
 inputFloor 
 
 
 The minimum level in the input range.   
 
 
 
 inputCeiling 
 
 
 The maximum level in the input range.   
 
 
 
 outputFloor 
 
 
 The minimum level in the output range. Default: 0.   
 
 
 
 outputCeiling 
 
 
 The maximum level in the output range. Default: 1023.   
 
 
          


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> pin - The pin on which to sense 

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id - The ID of this compoenent e.g. DEVICE_ID_THERMOMETER 

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleFloor

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleCeiling
<br/>
####LinearAnalogSensor( <div style='color:#a71d5d; display:inline-block'>Pin  &</div> pin,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleFloor,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleCeiling,  <div style='color:#a71d5d; display:inline-block'>float</div> valueFloor)
#####Description
Constructor.  

 Creates a  LinearAnalogSensor .  

   
 
 pin 
 
 
 The pin on which to sense   
 
 
 
 id 
 
 
 The ID of this compoenent e.g. DEVICE_ID_THERMOMETER   
 
 
 
 inputFloor 
 
 
 The minimum level in the input range.   
 
 
 
 inputCeiling 
 
 
 The maximum level in the input range.   
 
 
 
 outputFloor 
 
 
 The minimum level in the output range. Default: 0.   
 
 
 
 outputCeiling 
 
 
 The maximum level in the output range. Default: 1023.   
 
 
          


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> pin - The pin on which to sense 

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id - The ID of this compoenent e.g. DEVICE_ID_THERMOMETER 

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleFloor

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleCeiling

>  <div style='color:#a71d5d; display:inline-block'>float</div> valueFloor
<br/>
####LinearAnalogSensor( <div style='color:#a71d5d; display:inline-block'>Pin  &</div> pin,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleFloor,  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleCeiling,  <div style='color:#a71d5d; display:inline-block'>float</div> valueFloor,  <div style='color:#a71d5d; display:inline-block'>float</div> valueCeiling)
#####Description
Constructor.  

 Creates a  LinearAnalogSensor .  

   
 
 pin 
 
 
 The pin on which to sense   
 
 
 
 id 
 
 
 The ID of this compoenent e.g. DEVICE_ID_THERMOMETER   
 
 
 
 inputFloor 
 
 
 The minimum level in the input range.   
 
 
 
 inputCeiling 
 
 
 The maximum level in the input range.   
 
 
 
 outputFloor 
 
 
 The minimum level in the output range. Default: 0.   
 
 
 
 outputCeiling 
 
 
 The maximum level in the output range. Default: 1023.   
 
 
          


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>Pin  &</div> pin - The pin on which to sense 

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> id - The ID of this compoenent e.g. DEVICE_ID_THERMOMETER 

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleFloor

>  <div style='color:#a71d5d; display:inline-block'>uint16_t</div> sampleCeiling

>  <div style='color:#a71d5d; display:inline-block'>float</div> valueFloor

>  <div style='color:#a71d5d; display:inline-block'>float</div> valueCeiling
##updateSample
<br/>
####<div style='color:#a71d5d; display:inline-block'>void</div> <div style='color:#795da3; display:inline-block'>updateSample</div>()
#####Description
Updates the internal reading of the sensor. Typically called periodicaly.  

 


#####Returns
DEVICE_OK on success. 
____
[comment]: <> ({"end":"LinearAnalogSensor"})
