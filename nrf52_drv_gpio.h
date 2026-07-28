#ifndef NRF52_DRV_GPIO_H__
#define NRF52_DRV_GPIO_H__


#include <stdio.h>
#include <stdint.h>

#include "nrfx_gpiote.h"
#include "boards.h"

#include "user_define.h"
#include "input_ctrl.h"


#ifdef __cpluscplus
extern "C"{
#endif

#define OUTPUT              0x00
#define INPUT               0x01

#define HIGH_STATE          0x01
#define LOW_STATE           0x00


typedef struct 
{
    nrf_gpiote_polarity_t   edge;
    nrf_gpio_pin_pull_t     pull_config;
    nrf_gpiote_outinit_t    init;
    uint8_t pin_number;
    uint8_t direct;
}_strGPIO;



void Init_GPIO(_strGPIO config);
uint32_t Read_GPIO(uint32_t pin);
void Write_GPIO_State(uint32_t pin, uint8_t state);


#ifdef __cplusplus
extern }
#endif

#endif

//End of File

