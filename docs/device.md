#About the micro:bit

![microbit from the front and the back](resources/microbit_front_back.png)

The central processing unit (CPU) for the micro:bit is the [Nordic nRF51822](https://www.nordicsemi.com/eng/Products/Bluetooth-Smart-Bluetooth-low-energy/nRF51822)
and it controls all functionality offered by the micro:bit.

On board the micro:bit there is already:

- a 5 x 5 LED matrix [display](ubit/display.md).
- 2 programmable [buttons](ubit/button.md).
- a 3-axis [accelerometer](ubit/accelerometer.md).
- an [e-compass](ubit/compass.md).
- [Bluetooth](ubit/blemanager.md).
- 20 user controlled [pins](ubit/io.md), with Analog and Digital capabilities.
- [serial](ubit/serial.md) capabilities over USB and the edge connector.

##Datasheets

<div class="col-sm-4">
    <h3>Nordic nRF51822</h3>
    <p>
        The central processing unit of the micro:bit, the nRF51822, controls and drives all functionality on
        the micro:bit.
    </p>
    <p>
        <a target="_blank" href="../resources/datasheets/nRF51822.pdf" class="btn btn-lg btn-outline">
            Datasheet
        </a>
    </p>
</div>
<div class="col-sm-4">
    <h3>NXP MAG3110</h3>
    <p>
        The MAG3110 magnetometer is used in conjunction with with the 3-axis accelerometer
        (MMA8653) to create an e-compass.
    </p>
    <p>
        <a target="_blank" href="../resources/datasheets/MAG3110.pdf" class="btn btn-lg btn-outline">
            Datasheet
        </a>
    </p>
</div>
<div class="col-sm-4">
    <h3>NXP MMA8653</h3>
    <p>
        The MMA8653 accelerometer provides orientation and acceleration information
        of the micro:bit.
    </p>
    <p>
        <a target="_blank" href="../resources/datasheets/MMA8653.pdf" class="btn btn-lg btn-outline">
            Datasheet
        </a>
    </p>
</div>
