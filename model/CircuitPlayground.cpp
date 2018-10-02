/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

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

#include "CodalConfig.h"
#include "CircuitPlayground.h"
#include "CodalDmesg.h"
#include "Timer.h"
#include "neopixel.h"

using namespace codal;

#ifdef DEVICE_DBG
RawSerial *SERIAL_DEBUG;
#endif

void cplay_dmesg_flush();
CircuitPlayground* cplay_device_instance = NULL;

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

#define NVM_SW_CALIB_DFLL48M_COARSE_VAL 58
#define NVM_SW_CALIB_DFLL48M_FINE_VAL 64


int target_seed_random(uint32_t rand)
{
    return codal::seed_random(rand);
}

int target_random(int max)
{
    return codal::random(max);
}

//
// TODO: Refactor this into a CPU control or power class...
//
void cpu_clock_init(void) {

    NVMCTRL->CTRLB.bit.RWS = 1;

    /* Configure OSC8M as source for GCLK_GEN 2 */
    GCLK->GENDIV.reg = GCLK_GENDIV_ID(2);  // Read GENERATOR_ID - GCLK_GEN_2
    gclk_sync();

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(2) | GCLK_GENCTRL_SRC_OSC8M_Val | GCLK_GENCTRL_GENEN;
    gclk_sync();

    // Turn on DFLL with USB correction and sync to internal 8 mhz oscillator
    SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_ENABLE;
    dfll_sync();

    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    SYSCTRL_DFLLVAL_Type dfllval_conf = {0};
    uint32_t coarse =( *((uint32_t *)(NVMCTRL_OTP4)
                + (NVM_SW_CALIB_DFLL48M_COARSE_VAL / 32))
            >> (NVM_SW_CALIB_DFLL48M_COARSE_VAL % 32))
        & ((1 << 6) - 1);
    if (coarse == 0x3f) {
        coarse = 0x1f;
    }
    dfllval_conf.bit.COARSE  = coarse;
    // TODO(tannewt): Load this from a well known flash location so that it can be
    // calibrated during testing.
    dfllval_conf.bit.FINE    = 0x1ff;

    SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP( 0x1f / 4 ) | // Coarse step is 31, half of the max value
        SYSCTRL_DFLLMUL_FSTEP( 10 ) |
        48000;

    SYSCTRL->DFLLVAL.reg = dfllval_conf.reg;
    SYSCTRL->DFLLCTRL.reg = 0;
    dfll_sync();
    SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_MODE |
        SYSCTRL_DFLLCTRL_CCDIS |
        SYSCTRL_DFLLCTRL_USBCRM | /* USB correction */
        SYSCTRL_DFLLCTRL_BPLCKC;
    dfll_sync();
    SYSCTRL->DFLLCTRL.reg |= SYSCTRL_DFLLCTRL_ENABLE ;
    dfll_sync();

    GCLK_CLKCTRL_Type clkctrl={0};
    uint16_t temp;
    GCLK->CLKCTRL.bit.ID = 2; // GCLK_ID - DFLL48M Reference
    temp = GCLK->CLKCTRL.reg;
    clkctrl.bit.CLKEN = 1;
    clkctrl.bit.WRTLOCK = 0;
    clkctrl.bit.GEN = GCLK_CLKCTRL_GEN_GCLK0_Val;
    GCLK->CLKCTRL.reg = (clkctrl.reg | temp);

    // Configure DFLL48M as source for GCLK_GEN 0
    GCLK->GENDIV.reg = GCLK_GENDIV_ID(0);
    gclk_sync();

    // Add GCLK_GENCTRL_OE below to output GCLK0 on the SWCLK pin.
    GCLK->GENCTRL.reg =
        GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;

    gclk_sync();
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
    io(),
    serial(io.a7, io.a6),
    buttonA(io.buttonA, DEVICE_ID_BUTTON_A, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_HIGH, PullMode::Down),
    buttonB(io.buttonB, DEVICE_ID_BUTTON_B, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_HIGH, PullMode::Down),
    buttonC(io.buttonC, DEVICE_ID_BUTTON_C, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up),
    buttonAB(DEVICE_ID_BUTTON_A, DEVICE_ID_BUTTON_B, DEVICE_ID_BUTTON_AB),
    i2c(io.sda, io.scl),
    flashSPI(io.flashMOSI, io.flashMISO, io.flashSCLK),
    coordinateSpace(SIMPLE_CARTESIAN, false, COORDINATE_SPACE_ROTATED_0),
    accelerometer(i2c, io.int1, coordinateSpace),
    thermometer(io.temperature, DEVICE_ID_THERMOMETER, 20, 10000, 3380, 10000, 273.5),
    lightSensor(io.light, DEVICE_ID_LIGHT_SENSOR)
{

    cplay_device_instance = this;
    // Clear our status
    status = 0;
    cpu_clock_init();

    codal_dmesg_set_flush_fn(cplay_dmesg_flush);

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
    this->seedRandom(thermometer.getValue() * lightSensor.getValue());

    // light sensor is very stable, so reflect this in the tuning parameters of the driver.
    lightSensor.setSensitivity(912);
    lightSensor.setPeriod(50);

    // clear neopixels
    uint8_t neopixelOff[30];
    memset(neopixelOff, 0x00, sizeof(neopixelOff));
    // for whatever reason to first send doesn't quite work
    neopixel_send_buffer(io.neopixel, neopixelOff, sizeof(neopixelOff));
    target_wait(1);
    neopixel_send_buffer(io.neopixel, neopixelOff, sizeof(neopixelOff));

    flashSPI.setFrequency(4000000);
    flashSPI.setMode(0);
}

/**
  * A listener to perform actions as a result of Message Bus reflection.
  *
  * In some cases we want to perform lazy instantiation of components, such as
  * the compass and the accelerometer, where we only want to add them to the idle
  * fiber when someone has the intention of using these components.
  */
void CircuitPlayground::onListenerRegisteredEvent(Event evt)
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

/**
 * A periodic callback invoked by the fiber scheduler idle thread.
* We use this for any low priority, backgrounf housekeeping.
*
*/
void CircuitPlayground::idleCallback()
{
    codal_dmesg_flush();
}

void cplay_dmesg_flush()
{
#if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
#if DEVICE_DMESG_BUFFER_SIZE > 0

    if (codalLogStore.ptr > 0 && cplay_device_instance)
    {
        for (uint32_t i=0; i<codalLogStore.ptr; i++)
            ((CircuitPlayground *)cplay_device_instance)->serial.putc(codalLogStore.buffer[i]);

        codalLogStore.ptr = 0;
    }
#endif
#endif
}

