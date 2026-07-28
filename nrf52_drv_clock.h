#ifndef NRF52_DRV_CLOCK_H__
#define NRF52_DRV_CLOCK_H__

#include <stdio.h>
#include <stdint.h>

#include "nrf_drv_clock.h"

#include "app_error.h"

#ifdef __cplusplus
extern "C"{
#endif

#define CLOCK_SRC_EXT   0x01
#define CLOCK_SRC_INT   0x02

#define CLOCK_LF        0x01
#define CLOCK_HF        0x02

void Init_Clocks(uint8_t clk_flag);

#ifdef __cplusplus
}
#endif
#endif

//End of File
