#include "nrf52_drv_systick.h"

volatile uint32_t systick_ms = 0;

void SysTick_Handler(void)
{
    ++systick_ms;
    --milli_sec;
}


/** @brief          Set tick time of Systick as 1msec
 * 
 */
void Init_Systick(void)
{
    SysTick_Config(SystemCoreClock / 1000UL);
    NVIC_EnableIRQ(SysTick_IRQn);
}


//End of File
