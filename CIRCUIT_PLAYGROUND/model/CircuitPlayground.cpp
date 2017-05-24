/*
The MIT License (MIT)

Copyright (c) 2016 Lancaster University, UK.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "DeviceConfig.h"
#include "CircuitPlayground.h"
#include "Timer.h"

using namespace codal;

CodalDevice& device;

#ifdef DEVICE_DBG
RawSerial *SERIAL_DEBUG;
#endif
static void gclk_sync(void)
{
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY)
        ;
}

static void dfll_sync(void)
{
    while ((SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0)
        ;
}

#undef ENABLE

#define CPU_FREQUENCY 48000000
#define NVM_SW_CALIB_DFLL48M_COARSE_VAL 58
#define NVM_SW_CALIB_DFLL48M_FINE_VAL 64

static void mysystem_init(void)
{
    NVMCTRL->CTRLB.bit.RWS = 1;

    // Turn on DFLL with USB correction and sync to internal 8 mhz oscillator
    SYSCTRL->DFLLCTRL.bit.ONDEMAND = 0;
    dfll_sync();

#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

    SYSCTRL_DFLLCTRL_Type dfllctrl_conf = {0};
    SYSCTRL_DFLLVAL_Type dfllval_conf = {0};
    uint32_t coarse = (*((uint32_t *)(NVMCTRL_OTP4) + (NVM_SW_CALIB_DFLL48M_COARSE_VAL / 32)) >>
                       (NVM_SW_CALIB_DFLL48M_COARSE_VAL % 32)) &
                      ((1 << 6) - 1);
    if (coarse == 0x3f)
    {
        coarse = 0x1f;
    }
    uint32_t fine = (*((uint32_t *)(NVMCTRL_OTP4) + (NVM_SW_CALIB_DFLL48M_FINE_VAL / 32)) >>
                     (NVM_SW_CALIB_DFLL48M_FINE_VAL % 32)) &
                    ((1 << 10) - 1);
    if (fine == 0x3ff)
    {
        fine = 0x1ff;
    }
    dfllval_conf.bit.COARSE = coarse;
    dfllval_conf.bit.FINE = fine;
    dfllctrl_conf.bit.USBCRM = 1; // usb correction
    dfllctrl_conf.bit.BPLCKC = 0;
    dfllctrl_conf.bit.QLDIS = 0;
    dfllctrl_conf.bit.CCDIS = 1;
    dfllctrl_conf.bit.ENABLE = 1;

    SYSCTRL->DFLLMUL.reg = 48000;
    SYSCTRL->DFLLVAL.reg = dfllval_conf.reg;
    SYSCTRL->DFLLCTRL.reg = dfllctrl_conf.reg;

    GCLK->CLKCTRL.bit.ID = 0; // GCLK_ID - DFLL48M Reference
    gclk_sync();

    GCLK->CLKCTRL.bit.CLKEN = 1;
    GCLK->CLKCTRL.bit.WRTLOCK = 0;
    GCLK->CLKCTRL.bit.GEN = 0;

    // Configure DFLL48M as source for GCLK_GEN 0
    GCLK->GENDIV.bit.ID = 0;
    gclk_sync();
    GCLK->GENDIV.reg = 0;

    GCLK->GENCTRL.bit.ID = 0;
    gclk_sync();
    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
}

/**
  * Constructor.
  *
  * Create a representation of a GenuinoZero device, which includes member variables
  * that represent various device drivers used to control aspects of the micro:bit.
  */
CircuitPlayground::CircuitPlayground() :
    messageBus(),
    timer(),
    serial(TXD, RXD),
    io(),
    buttonA(io.buttonA, DEVICE_ID_BUTTON_A, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_HIGH, PullDown),
    buttonB(io.buttonB, DEVICE_ID_BUTTON_B, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_HIGH, PullDown),
    buttonC(io.buttonC, DEVICE_ID_BUTTON_C, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullUp),
    buttonAB(DEVICE_ID_BUTTON_A, DEVICE_ID_BUTTON_B, DEVICE_ID_BUTTON_AB),
    i2c(LIS_SDA, LIS_SCL),
    accelerometer(i2c, io.int1, LIS3DH_DEFAULT_ADDR, DEVICE_ID_ACCELEROMETER, NORTH_EAST_UP),
    thermometer(io.temperature, DEVICE_ID_THERMOMETER, 25, 10000, 3380, 10000, 273.5),
    lightSensor(io.light, DEVICE_ID_LIGHT_SENSOR)
{
    // Clear our status
    status = 0;
    mysystem_init();

    // Bring up fiber scheduler.
    scheduler_init(messageBus);

    messageBus.listen(DEVICE_ID_MESSAGE_BUS_LISTENER, DEVICE_EVT_ANY, this, &CircuitPlayground::onListenerRegisteredEvent);

    for(int i = 0; i < DEVICE_COMPONENT_COUNT; i++)
    {
        if(CodalComponent::components[i])
            CodalComponent::components[i]->init();
    }

    //
    // Device specific configuraiton
    //

    // Seed our random number generator
    device.seedRandom(thermometer.getValue() * lightSensor.getValue());

    // light sensor is very stable, so reflect this in the tuning parameters of the driver.
    lightSensor.setSensitivity(912);
    lightSensor.setPeriod(50);
}

/**
  * A listener to perform actions as a result of Message Bus reflection.
  *
  * In some cases we want to perform lazy instantiation of components, such as
  * the compass and the accelerometer, where we only want to add them to the idle
  * fiber when someone has the intention of using these components.
  */
void CircuitPlayground::onListenerRegisteredEvent(DeviceEvent evt)
{
    switch(evt.value)
    {
        case DEVICE_ID_BUTTON_AB:
            // A user has registered to receive events from the buttonAB multibutton.
            // Disable click events from being generated by ButtonA and ButtonB, and defer the
            // control of this to the multibutton handler.
            //
            // This way, buttons look independent unless a buttonAB is requested, at which
            // point button A+B clicks can be correclty handled without breaking
            // causal ordering.
            buttonA.setEventConfiguration(DEVICE_BUTTON_SIMPLE_EVENTS);
            buttonB.setEventConfiguration(DEVICE_BUTTON_SIMPLE_EVENTS);
            buttonAB.setEventConfiguration(DEVICE_BUTTON_ALL_EVENTS);
            break;

        case DEVICE_ID_ACCELEROMETER:
        case DEVICE_ID_GESTURE:
            // A listener has been registered for the accelerometer.
            // The accelerometer uses lazy instantiation, we just need to read the data once to start it running.
            accelerometer.updateSample();
            break;

        case DEVICE_ID_THERMOMETER:
            // A listener has been registered for the thermometer.
            // The thermometer uses lazy instantiation, we just need to read the data once to start it running.
            thermometer.updateSample();
            break;

        case DEVICE_ID_LIGHT_SENSOR:
            // A listener has been registered for the light sensor.
            // The light sensor uses lazy instantiation, we just need to read the data once to start it running.
            lightSensor.updateSample();
            break;
    }
}
