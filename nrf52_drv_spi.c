#include "nrf52_drv_spi.h"


static uint8_t LED_arr[SPI_LEDNUM * DIGITAL_LED_BYTE];

volatile uint16_t spi_flag = 0;

nrf_drv_spi_t nrf_SPI = NRF_DRV_SPI_INSTANCE(NRF_SPI_DRV_NUM);


/**
 * 
 */
void skc6812_spi_handler(nrf_drv_spi_evt_t const * p_event, void * p_context)
{
    if (p_event->type == NRF_DRV_SPI_EVENT_DONE)
    {
        spi_flag = 0;           
    }    
}


/**
 * 
 */
void Init_SPI(void)
{
    uint32_t err_code;
    nrf_drv_spi_config_t skc6812_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    
    skc6812_config.mosi_pin  = MOSI_PIN;
    skc6812_config.sck_pin   = SCK_PIN;
    skc6812_config.frequency = NRF_DRV_SPI_FREQ_4M;
    skc6812_config.mode      = NRF_DRV_SPI_MODE_1;
    skc6812_config.orc       = 0x00;
    
    err_code = nrf_drv_spi_init(&nrf_SPI, &skc6812_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);   
}


/**
 * 
 */
void Transmit_SPI(uint16_t len)
{
    uint32_t err_code = 0;
    uint32_t reptite = 0;
    uint16_t data_len = len;
    uint8_t quot = data_len / SPI_PACKET_SIZE;
    uint8_t rem = data_len % SPI_PACKET_SIZE;

    while (reptite < quot)
    {
        err_code = nrf_drv_spi_transfer(&nrf_SPI, &LED_arr[reptite * SPI_PACKET_SIZE], SPI_PACKET_SIZE, NULL, 0);
        ++reptite;
        APP_ERROR_CHECK(err_code);
    }
    
    err_code = nrf_drv_spi_transfer(&nrf_SPI, &LED_arr[quot * SPI_PACKET_SIZE], rem, NULL, 0);
    APP_ERROR_CHECK(err_code);
}


/**
 * 
 */
void Set_Digital_LED_Data(sColorRGBW_t *color_array)
{
    uint8_t bit_idx = 0;
    uint32_t grbw_value[SPI_LEDNUM] = {0,};

    RGBW_to_GRBW(&grbw_value[0], &color_array[0], SPI_LEDNUM);

    for (uint8_t led_idx = 0; led_idx < SPI_LEDNUM; led_idx++)
    {
        for (bit_idx = 0; bit_idx < DIGITAL_LED_BYTE; bit_idx++)
        {
            if (grbw_value[led_idx]>>(31 - bit_idx) & AND_BIT)
            {
                LED_arr[(led_idx * DIGITAL_LED_BYTE) + bit_idx] = LED_4MHZ_HIGH;
            }
            else
            {
                LED_arr[(led_idx * DIGITAL_LED_BYTE) + bit_idx] = LED_4MHZ_LOW;
            }            
        }
    }
    
    Transmit_SPI(SPI_LEDNUM * DIGITAL_LED_BYTE);
}


//End of File
