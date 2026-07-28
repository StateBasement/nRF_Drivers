#ifndef NRFX52_DRV_SPI_H__
#define NRFX52_DRV_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nrf_drv_spi.h"

#include "app_color.h"
#include "user_define.h"

#define MOSI_PIN                    USER_SPI_MOSI_PIN
#define SCK_PIN                     USER_SPI_CLK_PIN
#define MISO_PIN                    USER_SPI_MISO_PIN
#define NRF_SPI_DRV_NUM             0


#define SPI_PACKET_SIZE             0xF0
#define COLOR_CHANNEL               4

#define LED_BIT_NUM                 8        //Bit number of Byte

// #define SKC6812_BYTE_NUM            32       //Integrate to DIGITAL_LED_BYTE
// #define WS2812_BYTE_NUM             24       //Integrate to DIGITAL_LED_BYTE
#define DIGITAL_LED_BYTE            (COLOR_CHANNEL * 8)

// #define SKC6812_BIT_HIGH            0xFE     //Integrate to DIGITAL_LED_BIT_HIGH
// #define SKC6812_BIT_LOW             0xC0     //Integrate to DIGITAL_LED_BIT_LOW

// #define WS2812_BIT_HIGH             0xFE     //Integrate to DIGITAL_LED_BIT_HIGH
// #define WS2812_BIT_LOW              0xC0     //Integrate to DIGITAL_LED_BIT_LOW
#define DIGITAL_LED_BIT_HIGH        0xFC        //0xFC
#define DIGITAL_LED_BIT_LOW         0xE0        //0xC0

#define LED_4MHZ_HIGH               0xE0
#define LED_4MHZ_LOW                0x80

#define COLOR_MAX_VALUE             0xFF

// #define SKC6812_BYTE_LEN            16
#define AND_BIT                     0x01


typedef enum
{
    SKC6812_GREEN = 0,
    SKC6812_RED,
    SKC6812_BLUE,
    SKC6812_WHITE,
}skc6812_colot_t;


typedef enum
{
    PAIRING_ORANGE,
    PAIRING_YELLOW,
    PAIRING_GREEN,
    PAIRING_CYAN,
    PAIRING_BLUE,
    PAIRING_PURPLE,
    PAIRING_VIOLET
}pairing_color_t;

// static uint8_t skc6812_orange[] = {0x40, 0xFF, 0x00, 0x00};
// static uint8_t skc6812_yellow[] = {0x80, 0xFF, 0x00, 0x00};
// static uint8_t skc6812_green[] = {0xFF, 0x00, 0x00, 0x00};
// static uint8_t skc6812_cyan[] = {0xFF, 0x00, 0xFF, 0x00};
// static uint8_t skc6812_blue[] = {0x00, 0x00, 0xFF, 0x00};
// static uint8_t skc6812_purple[] = {0x00, 0xFF, 0x40, 0x00};
// static uint8_t skc6812_violet[] = {0x00, 0xFF, 0xFF, 0x00};

extern volatile uint16_t spi_state;

void Init_SPI(void);

void Set_Digital_LED_Data(sColorRGBW_t *color_array);


void Transmit_SPI(uint16_t len);

#ifdef __cplusplus
}
#endif

#endif // NRF52_DRV_SPI_H__




