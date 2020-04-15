/* Standard includes. */
#include <stdio.h>

#include "TM4C123GH6PM.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"

/* Definition of the functions implementing the tasks. */
static void vPeriodicTask(void *pvParameters);
static void vContinuousProcessingTask(void *pvParameters);

/* Parameters for our two continuous tasks.
 * Static so they are not on the stack, ensuring that
 * they remain valid when the tasks are executing. */
static unsigned led_continuous_1 = LED_RED;
static unsigned led_continuous_2 = LED_BLUE;

/*-----------------------------------------------------------*/

static void vContinuousProcessingTask(void* pvParameters)
{
    unsigned led = *(unsigned*)pvParameters;

    for (;;)
    {
        BSP_ledOn(led);
        BSP_ledOff(led);
    }
}

static void vPeriodicTask(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xDelay3ms = pdMS_TO_TICKS(500);

    /* The xLastWakeTime variable needs to be initialized with the current tick
     * count. Note that this is the only time the variable is explicitly written to.
     * After this xLastWakeTime is managed automatically by the vTaskDelayUntil()
     * API function. */
    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        BSP_ledGreenToggle();

        /* The task should execute every 3 milliseconds exactly. */
        vTaskDelayUntil(&xLastWakeTime, xDelay3ms);
    }
}

/*-----------------------------------------------------------*/

int main(void)
{
    SystemCoreClockUpdate();

    BSP_init();

    xTaskCreate(vPeriodicTask, /* The function that implements the task. */
                "Periodic", /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
                NULL, /* The parameter passed to the task - just to check the functionality. */
                2, /* The priority assigned to the task. */
                NULL); /* The task handle is not required, so NULL is passed. */

    xTaskCreate(vContinuousProcessingTask, "Continuous 1",
                configMINIMAL_STACK_SIZE, &led_continuous_1,
                1, NULL);

    xTaskCreate(vContinuousProcessingTask, "Continuous 2",
                    configMINIMAL_STACK_SIZE, &led_continuous_2,
                    1, NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached. If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks to be created. See the memory management section on the
     * FreeRTOS web site for more details. */
    for (;;) {}

    return 0;
}

/*
 * Run time stack overflow checking is performed if
 * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.
 * This hook function is called if a stack overflow is detected.
 */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    for (;;) {}
}
