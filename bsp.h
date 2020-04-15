/* Board Support Package for Tiva LaunchPad */

#ifndef __BSP_H__
#define __BSP_H__

#include <stdio.h>

#include "TM4C123GH6PM.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* On-board LEDs. */
#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

/* On-board switch. */
#define BTN_SW1 (1u << 4)

/* Initialize the needed hardware and interrupts. */
void BSP_init( void );

void BSP_ledRedOn(void);
void BSP_ledRedOff(void);

void BSP_ledBlueOn(void);
void BSP_ledBlueOff(void);
void BSP_ledBlueToggle(void);

void BSP_ledGreenOn(void);
void BSP_ledGreenOff(void);
void BSP_ledGreenToggle(void);

void BSP_ledOn(unsigned led);
void BSP_ledOff(unsigned led);

#endif // __BSP_H__
