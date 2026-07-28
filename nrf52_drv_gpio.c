
#include "nrf52_drv_gpio.h"


void GPIO_Handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    switch (action)
    {
        case NRF_GPIOTE_POLARITY_HITOLO:
            switch (pin)
            {        
                case USER_BUTTON_1:
                    // Write_GPIO_State(5, LOW_STATE);
                break;

                default:    //essential
                    // do nothing
                break;
            }
        break;

        case NRF_GPIOTE_POLARITY_LOTOHI:
            switch (pin)
            {
                default:    //essential
                    // do nothing
                break;
            }
        break;
        
        case NRF_GPIOTE_POLARITY_TOGGLE:
            switch (pin)
            {        
                case USER_TILT_PIN:
                    // Set_Tilt_Count(Get_Tilt_Count()+1);
                break;
        
                default:    //essential
                    // do nothing
                break;
            }
        break;

        default:
            // do nothing
        break;
    }
}



void Init_GPIO(_strGPIO config)
{
    uint32_t err_code;

    if(!nrfx_gpiote_is_init())
    {
        err_code = nrfx_gpiote_init();
        APP_ERROR_CHECK(err_code);
    }
    
    switch (config.direct)
    {
        case INPUT:
            {
                nrfx_gpiote_in_config_t in_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
                in_config.pull  = config.pull_config;
                in_config.sense = config.edge;

                err_code = nrfx_gpiote_in_init(config.pin_number, &in_config ,GPIO_Handler);
                APP_ERROR_CHECK(err_code);
                
                nrfx_gpiote_in_event_enable(config.pin_number, true);
            }
        break;
        
        case OUTPUT:
            {
                nrfx_gpiote_out_config_t out_config = NRFX_GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_LOW);
                out_config.task_pin = config.pin_number;
                out_config.init_state = config.init;

                err_code = nrfx_gpiote_out_init(config.pin_number, &out_config);
                APP_ERROR_CHECK(err_code);
            }
        break;

        default:
            // do nothing
        break;
    }
}


uint32_t Read_GPIO(uint32_t pin)
{
    return (uint32_t)nrfx_gpiote_in_is_set(pin);
}


void Write_GPIO_State(uint32_t pin, uint8_t state)
{
    switch (state)
    {
        case HIGH_STATE:
            nrfx_gpiote_out_set(pin);        
        break;
        
        case LOW_STATE:
            nrfx_gpiote_out_clear(pin);
        break;

        default:
            // do nothing
        break;
    }
}

//End of File
