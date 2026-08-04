#ifndef NRF52_DRV_GPIO_H__
#define NRF52_DRV_GPIO_H__


#include <stdint.h>

#include "nrfx_gpiote.h"


#include "input_ctrl.h"


#ifdef __cpluscplus
extern "C"{
#endif


#define HIGH_STATE          0x01
#define LOW_STATE           0x00



typedef enum
{
    INPUT,
    OUTPUT
}eDirect_t;


typedef struct 
{
    nrf_gpio_pin_pull_t     pull_config;
    nrf_gpiote_outinit_t    init;
    nrf_gpiote_polarity_t   edge;
    eDirect_t               direct;
    uint8_t                 pin_number;
}sGPIO_config_t;



void Init_GPIO(sGPIO_config_t config);
uint32_t Read_GPIO(uint32_t pin);
void Write_GPIO_State(uint32_t pin, uint8_t state);


#ifdef __cplusplus
extern }
#endif

#endif

//End of File

