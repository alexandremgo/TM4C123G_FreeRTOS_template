#include "bsp.h"

void BSP_init(void)
{
    /* Enable clock for GPIOF. */
    SYSCTL->RCGC2 |= (1U << 5);
    /* Enable Advanced High-Performance Bus for GPIOF. */
    SYSCTL->GPIOHBCTL |= (1U << 5);

    /* Set GPIO Pin Direction as output. */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    /* Set Digital Enable. */
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    /* Configure switch SW1. */
    GPIOF_AHB->DIR &= ~BTN_SW1; /* input */
    GPIOF_AHB->DEN |= BTN_SW1; /* digital enable */
    GPIOF_AHB->PUR |= BTN_SW1; /* pull-up resistor enable */

    /* GPIO interrupt setup for SW1. */
    GPIOF_AHB->IS &= ~BTN_SW1; /* edge detect for SW1 */
    GPIOF_AHB->IBE &= ~BTN_SW1; /* only one edge generate the interrupt */
    GPIOF_AHB->IEV &= ~BTN_SW1; /* a falling edge triggers the interrupt */
    GPIOF_AHB->IM |= BTN_SW1; /* enable GPIOF interrupt for SW1 */

    /* Enable the GPIO interrupt for SW1. */
    NVIC_SetPriority(GPIOF_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(GPIOF_IRQn);

}

/***** LED handlers *****/

void BSP_ledRedOn(void)
{
    GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
}

void BSP_ledRedOff(void)
{
    GPIOF_AHB->DATA_Bits[LED_RED] = 0U;
}

void BSP_ledBlueOn(void)
{
    GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
}

void BSP_ledBlueOff(void)
{
    GPIOF_AHB->DATA_Bits[LED_BLUE] = 0U;
}

void BSP_ledGreenOn(void)
{
    GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
}

void BSP_ledGreenOff(void)
{
    GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
}

void BSP_ledGreenToggle(void)
{
    GPIOF_AHB->DATA ^= LED_GREEN;
}

void BSP_ledOn(uint8_t led)
{
    if(led == LED_RED || led == LED_BLUE || led == LED_GREEN) {
        GPIOF_AHB->DATA_Bits[led] = led;
    }
}

void BSP_ledOff(uint8_t led)
{
    if(led == LED_RED || led == LED_BLUE || led == LED_GREEN) {
        GPIOF_AHB->DATA_Bits[led] = 0U;
    }
}


/***** IRQ Handlers *****/

void GPIOPortF_IRQHandler(void)
{
    /* Variable used to check interrupt in debug mode. */
    static volatile uint32_t ux = 0;

    /* GPIO Raw Interrupt Status: check interrupt caused by SW1. */
    if ((GPIOF_AHB->RIS & BTN_SW1) != 0u)
    {
        ux++;
    }

    /* GPIO Interrupt Clear: clear interrupt sources. */
    GPIOF_AHB->ICR = 0xFFU;
}
