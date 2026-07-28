#ifndef NRF52_DRV_PWM_H__
#define NRF52_DRV_PWM_H__

#include <stdio.h>
#include <stdint.h>

#include "nrf_drv_pwm.h"
#include "user_define.h"
#include "app_color.h"
#include "led_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif


void Init_PWM_Driver(void);
void Set_PWM_Value(sColorRGBI_t rgbw_vlaue);
void Stop_PWM(void);

#ifdef __cplusplus
}
#endif


#endif


//end of File
