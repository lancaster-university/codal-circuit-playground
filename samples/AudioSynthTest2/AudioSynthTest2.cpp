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
#include "SAMD21PDM.h"
#include "Synthesizer.h"
#include "LevelDetector.h"

CircuitPlayground cplay;
SAMD21DMAC dmac;
SAMD21PDM microphone(cplay.io.microphoneData, cplay.io.microphoneClock, dmac, 10000);
LevelDetector level(microphone.output, 70, 30);
Synthesizer synth;
SAMD21DAC dac(cplay.io.speaker, dmac, synth.output, 44100);

int freq = 261;

void onClickA(DeviceEvent)
{
    synth.setFrequency(freq, 100);
}

void onClickB(DeviceEvent)
{
    synth.setFrequency(freq, 200);
}

void
onLoud(DeviceEvent)
{
    synth.setFrequency(2*freq, 200);
}

int main()
{
    // Align Synthesizer sample rate to playaout rate of the speaker DAC.
    synth.setSampleRate(dac.getSampleRate());
    synth.setTone(Synthesizer::SawtoothTone);

    microphone.enable();

    cplay.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onClickA);
    cplay.messageBus.listen(DEVICE_ID_BUTTON_B, DEVICE_BUTTON_EVT_CLICK, onClickB);
    cplay.messageBus.listen(DEVICE_ID_SYSTEM_LEVEL_DETECTOR, LEVEL_THRESHOLD_HIGH, onLoud);

    // All done. Release this fiber back to the scheduler for recycling. 
    release_fiber();
}


