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
#include "codal_target_hal.h"
#include "Timer.h"
#include "CodalDmesg.h"
#include "CodalCompat.h"

static int8_t irq_disabled;
void target_enable_irq()
{
    irq_disabled--;
    if (irq_disabled <= 0) {
        irq_disabled = 0;
        __enable_irq();
    }
}

void target_disable_irq()
{
    __disable_irq();
    irq_disabled++;
}

void target_wait_for_event()
{
    __WFE();
}

int target_seed_random(uint32_t rand)
{
    return codal::seed_random(rand);
}

int target_random(int max)
{
    return codal::random(max);
}

void target_wait_us(uint32_t us)
{
    codal::system_timer_wait_us(us);
}

void target_wait(uint32_t milliseconds)
{
    target_wait_us(milliseconds * 1000);
}

void target_reset()
{
    NVIC_SystemReset();
}

// 128 bits starting from here...
uint32_t* const serial_start = (uint32_t *)0x0080A00C;
uint64_t target_get_serial()
{
    return *((uint64_t*)serial_start);
}

__attribute__((weak))
void target_panic(int statusCode)
{
    target_disable_irq();

#if DEVICE_DMESG_BUFFER_SIZE > 0
    DMESG("*** CODAL PANIC : [%d]", statusCode);
    while (1)
    {
    }
#endif
}

/**
  *  Thread Context for an ARM Cortex M0 core.
  *
  * This is probably overkill, but the ARMCC compiler uses a lot register optimisation
  * in its calling conventions, so better safe than sorry!
  */
struct PROCESSOR_TCB
{
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R4;
    uint32_t R5;
    uint32_t R6;
    uint32_t R7;
    uint32_t R8;
    uint32_t R9;
    uint32_t R10;
    uint32_t R11;
    uint32_t R12;
    uint32_t SP;
    uint32_t LR;
    uint32_t stack_base;
};

PROCESSOR_WORD_TYPE fiber_initial_stack_base()
{
    return DEVICE_STACK_BASE;
}

void* tcb_allocate()
{
    return (void *)malloc(sizeof(PROCESSOR_TCB));
}

/**
  * Configures the link register of the given tcb to have the value function.
  *
  * @param tcb The tcb to modify
  * @param function the function the link register should point to.
  */
void tcb_configure_lr(void* tcb, PROCESSOR_WORD_TYPE function)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->LR = function;
}

/**
  * Configures the link register of the given tcb to have the value function.
  *
  * @param tcb The tcb to modify
  * @param function the function the link register should point to.
  */
void tcb_configure_sp(void* tcb, PROCESSOR_WORD_TYPE sp)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->SP = sp;
}

void tcb_configure_stack_base(void* tcb, PROCESSOR_WORD_TYPE stack_base)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->stack_base = stack_base;
}

PROCESSOR_WORD_TYPE tcb_get_stack_base(void* tcb)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    return tcbPointer->stack_base;
}

PROCESSOR_WORD_TYPE get_current_sp()
{
    return __get_MSP();
}

PROCESSOR_WORD_TYPE tcb_get_sp(void* tcb)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    return tcbPointer->SP;
}

void tcb_configure_args(void* tcb, PROCESSOR_WORD_TYPE ep, PROCESSOR_WORD_TYPE cp, PROCESSOR_WORD_TYPE pm)
{
    PROCESSOR_TCB* tcbPointer = (PROCESSOR_TCB *)tcb;
    tcbPointer->R0 = (uint32_t) ep;
    tcbPointer->R1 = (uint32_t) cp;
    tcbPointer->R2 = (uint32_t) pm;
}

extern PROCESSOR_WORD_TYPE __end__;
PROCESSOR_WORD_TYPE codal_heap_start = (PROCESSOR_WORD_TYPE)(&__end__);
