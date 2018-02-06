/*
The MIT License (MIT)

Copyright (c) 2016 Lancaster University.

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

#include "CircuitPlayground.h"
#include "SAMD21DAC.h"
#include "Synthesizer.h"

CircuitPlayground cplay;
SAMD21DMAC dmac;
Synthesizer synth;
SAMD21DAC dac(cplay.io.speaker, dmac, synth.output, 44100);

int freq = 300;

void onClickA(DeviceEvent)
{
    synth.setFrequency(2*freq, 500);
}

void onClickB(DeviceEvent)
{
    synth.setFrequency(1*freq, 100);
    synth.setFrequency(0, 100);
    synth.setFrequency(2*freq, 100);
    synth.setFrequency(0, 100);
    synth.setFrequency(3*freq, 100);
    synth.setFrequency(0, 100);
    synth.setFrequency(2*freq, 100);
    synth.setFrequency(0, 100);
    synth.setFrequency(3*freq, 100);
    synth.setFrequency(0, 100);
    synth.setFrequency(2*freq, 100);
}

int main()
{
    cplay.serial.printf("*** AudioSynthTest ***\n");

    // Align Synthesizer sample rate to playaout rate of the speaker DAC.
    synth.setSampleRate(dac.getSampleRate());
    synth.setTone(Synthesizer::SawtoothTone);

    synth.setFrequency(freq);

    // register for button clicks.
    cplay.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onClickA);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_CLICK, onClickB);

    // All done. Release this fiber back to the scheduler for recycling. 
    release_fiber();
}


