#cplay.i2c

##Overview

i2c is a very common, widely used protocol for communicating with other devices
over a wire. i2c uses a very simple addressing scheme to access these other
devices. The [accelerometer](accelerometer.md) uses I2C to communicate information.

##Message Bus ID

> None.

##Message Bus Events

> None.

##API
[comment]: <> ({"className":"I2C"})
##Constructor
<br/>
####I2C( <div style='color:#a71d5d; display:inline-block'>codal::Pin  &</div> sda,  <div style='color:#a71d5d; display:inline-block'>codal::Pin  &</div> scl)
#####Description
Constructor.


#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>codal::Pin  &</div> sda

>  <div style='color:#a71d5d; display:inline-block'>codal::Pin  &</div> scl
##setFrequency
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>setFrequency</div>( <div style='color:#a71d5d; display:inline-block'>uint32_t</div> frequency)
#####Description
Set the frequency of the  I2C  interface



 frequency


 The bus frequency in hertz





#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint32_t</div> frequency - The bus frequency in hertz
##write
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>write</div>( <div style='color:#a71d5d; display:inline-block'>uint8_t</div> data)
#####Description
Issues a standard, 2 byte  I2C  command write to the accelerometer.

 Blocks the calling thread until complete.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>uint8_t</div> data
#####Returns
DEVICE_OK on success, DEVICE_I2C_ERROR if the write request failed.
##read
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>read</div>()
#####Description
Issues a single-byte read command.

 Blocks the calling thread until complete.




#####Returns
the byte on success or DEVICE_I2C_ERROR if the read request failed.
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>read</div>( <div style='color:#a71d5d; display:inline-block'>AcknowledgeType</div> ack)
#####Description
Issues a single-byte read command.

 Blocks the calling thread until complete.




#####Parameters

>  <div style='color:#a71d5d; display:inline-block'>AcknowledgeType</div> ack
#####Returns
the byte on success or DEVICE_I2C_ERROR if the read request failed.
##start
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>start</div>()
#####Description



#####Returns
DEVICE_OK on success, or an error code
##stop
<br/>
####<div style='color:#a71d5d; display:inline-block'>int</div> <div style='color:#795da3; display:inline-block'>stop</div>()
#####Description



#####Returns
DEVICE_OK on success, or an error code
____
[comment]: <> ({"end":"I2C"})
