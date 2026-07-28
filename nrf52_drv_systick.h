#ifndef NRF_DRV_SYSTICK_H__
#define NRF_DRV_SYSTICK_H__

#include <stdio.h>
#include <stdint.h>

#include "nrf_drv_systick.h"
#include "system_nrf52.h"
#include "nrf52.h"
#include "app_systick.h"

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t systick_ms;

void Init_Systick(void);

#ifdef __cplusplus
}
#endif

#endif

// End of File
