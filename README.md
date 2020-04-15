# Simple Demo/Template of FreeRTOS for the Tiva TM4C123G LaunchPad

## Overview

This is a simple demo that uses FreeRTOS and the CMSIS definitions to create
3 tasks (one periodic and 2 continuous) that blink the 3 leds of the board, 
and an interrupt triggered by the button SW1 of the board.  
The configuration of FreeRTOS for the 
board is found in [FreeRTOSConfig.h](FreeRTOSConfig.h).

This demo can be used as a template for a new project using the TM4C123G LaunchPad and FreeRTOS.

The TivaWare™ Peripheral Driver Library is NOT used in this demo. The CMSIS was preferred.

## Sources and tutorials

The startup file, the GNU-ARM linker script and the CMSIS Cortex-M4 Peripheral Access Layer Header 
File for TM4C123GH6PM are taken from the tutorials made by Miro Samek. You can find 
the links to the tutorials here: http://www.state-machine.com/quickstart. They are great.

## Building the demo

### Toolset and IDE

The GNU-ARM toolset is used for this demo. The IDE Code Composer Studio has been used.

### FreeRTOS source files

The 4 FreeRTOS source files tasks.c, list.c, queue.c and timers.c are needed for this demo. 
They were put into the [FreeRTOS](FreeRTOS) folder. The 2 source files event_groups.c and croutine.c are 
unnecessary for this demo.

The source file port.c, the port of FreeRTOS to the MCU TM4C123GH6PM, is also needed, 
and was put in the [FreeRTOS/portable/GCC/ARM_CM4F](FreeRTOS/portable/GCC/ARM_CM4F) folder. 

Finally, the Memory Allocation scheme heap_1 is used for this demo, 
because no FreeRTOS object is freed in this demo. 
It was put in [FreeRTOS/portable/MemMang](FreeRTOS/portable/MemMang).  
See [the FreeRTOS doc](https://www.freertos.org/a00111.html) for more details.

### Header files

The header files for FreeRTOS are located in [FreeRTOS/include](FreeRTOS/include) and 
[FreeRTOS/portable/GCC/ARM_CM4F](FreeRTOS/portable/GCC/ARM_CM4F).
The CMSIS header files are located in [CMSIS/Include](CMSIS/Include). 
The path to those 3 directories need to be known by the compiler.