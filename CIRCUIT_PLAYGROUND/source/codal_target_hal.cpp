#include "mbed.h"
#include "codal_target_hal.h"

void target_enable_irq()
{
    __enable_irq();
}

void target_disable_irq()
{
    __disable_irq();
}

void target_wait_for_event()
{
    __WFE();
}

void target_wait(uint32_t milliseconds)
{
    wait_ms(milliseconds);
}

void target_reset()
{
    NVIC_SystemReset();
}

void target_panic(int statusCode)
{
    target_disable_irq();

#if DEVICE_DMESG_BUFFER_SIZE > 0
    DMESG("*** CODAL PANIC : [%d]", statusCode);
    while (1)
    {
    }
#else
    Serial pc(USBTX, USBRX);
    while (1)
    {
        pc.printf("*** CODAL PANIC : [%.3d]\n", statusCode);
        wait_ms(500);
    }
#endif
}
