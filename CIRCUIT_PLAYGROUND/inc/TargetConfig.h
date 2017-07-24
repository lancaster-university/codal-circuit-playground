#include "common_includes.h"
#include "device_types.h"

//
// Memory configuration
//
// The start address of usable RAM memory.
#ifndef DEVICE_SRAM_BASE
#define DEVICE_SRAM_BASE                      0x20000000
#endif

// Physical address of the top of SRAM.
#ifndef DEVICE_SRAM_END
#define DEVICE_SRAM_END                       0x20008000
#endif

// Physical address of the top of the system stack (on mbed-classic this is the top of SRAM)
#ifndef CORTEX_M0_STACK_BASE
#define CORTEX_M0_STACK_BASE                    DEVICE_SRAM_END
#endif

// Amount of memory reserved for the stack at the end of memory (bytes).
#ifndef DEVICE_STACK_SIZE
#define DEVICE_STACK_SIZE                     2048
#endif

// Physical address of the end of heap space.
#ifndef CODAL_HEAP_START
                                              extern uint32_t __end__;
#define CODAL_HEAP_START                      (uint32_t)(&__end__)
#endif

// Physical address of the end of heap space.
#ifndef CODAL_HEAP_END
#define CODAL_HEAP_END                        (CORTEX_M0_STACK_BASE - DEVICE_STACK_SIZE)
#endif

// Enable this to read 10 bits of data from the acclerometer.
// Otherwise, 8 bits are used.
// Set '1' to enable.
#ifndef USE_ACCEL_LSB
#define USE_ACCEL_LSB                           0
#endif

#define TARGET_DEBUG_CLASS                      RawSerial
