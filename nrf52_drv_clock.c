#include "nrf52_drv_clock.h"



void clock_Event_Handler(nrf_drv_clock_evt_type_t event)
{
    switch (event)
    {
        case NRF_DRV_CLOCK_EVT_HFCLK_STARTED:        
        break;

        case NRF_DRV_CLOCK_EVT_LFCLK_STARTED:
        break;

        case NRF_DRV_CLOCK_EVT_CAL_DONE:
        break;

        case NRF_DRV_CLOCK_EVT_CAL_ABORTED:
        break;

        default:
        break;
    }
}


/** @brief          Initialize main clock
 * 
 */
void Init_Clocks(uint8_t clk_flag)
{
    uint32_t err_code = 0;
    
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    
    // lf src init
    if (clk_flag || CLOCK_LF)
    {
        //If needed
        // nrf_drv_clock_handler_item_t lf_item;
        // lf_item.p_next = NULL;
        // lf_item.event_handler = clock_Event_Handler;

        nrf_drv_clock_lfclk_request(NULL);

        /** request event is irq
         * __SEV set Event register
         * __WFE clear Event register. or event register is clear mcu go to sleep.
         * pending IRQ will wake up the MCU from __WFE.
         */
        while (!nrf_drv_clock_lfclk_is_running())
        {
            __SEV();
            __WFE();
            __WFE();
        }
        
    }
    // hf src init
    if (clk_flag || CLOCK_HF)
    {
        //  if needed
        // nrf_drv_clock_handler_item_t hf_item;
        // hf_item.p_next = NULL;
        // hf_item.event_handler = clock_Event_Handler;         
        nrf_drv_clock_hfclk_request(NULL);

        while (!nrf_drv_clock_hfclk_is_running())
        {
            __SEV();
            __WFE();
            __WFE();
        }
    }    
}

//End of File
