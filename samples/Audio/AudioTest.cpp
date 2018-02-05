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

#define BUFFER_SIZE    22

CircuitPlayground cplay;
Synthesizer synth;
SAMD21DMAC dmac;
SAMD21DAC dac(cplay.io.speaker, dmac, synth.output);

uint16_t buf[BUFFER_SIZE];

void dac_test()
{
    // Test polled output

    while(1)
    {
        dac.setValue(0);
        wait_us(1136);
        dac.setValue(1023);
        wait_us(1136);
    }
}

void dma_test()
{
    // Test DMA output
    while(1)
        dac.play(buf, BUFFER_SIZE);
}

void synth_test() {
    synth.setFrequency(440);
    while(true) {
        cplay.io.led.setDigitalValue(1);
        synth.setVolume(200);
        cplay.sleep(500);        

        cplay.io.led.setDigitalValue(0);
        synth.setVolume(0);
        cplay.sleep(500);        
    }
}

int main()
{
   for (int i=0; i < BUFFER_SIZE/2; i++)
      buf[i] = 0;

   for (int i=BUFFER_SIZE/2; i < BUFFER_SIZE; i++)
      buf[i] = 1023;

    cplay.serial.printf("3...");
    wait_ms(1000);
    cplay.serial.printf("2...");
    wait_ms(1000);
    cplay.serial.printf("1...\n\n");
    wait_ms(1000);

    //dac_test();
    //dma_test();
    synth_test();
}


