#include "nrf52_drv_pwm.h"

static nrf_drv_pwm_t    m_pwm_bulb = NRF_DRV_PWM_INSTANCE(0);
static nrf_pwm_values_individual_t pwm_values;
static nrf_pwm_sequence_t const    pwm_seq =
{
    .values.p_individual = &pwm_values,
    .length              = NRF_PWM_VALUES_LENGTH(pwm_values),
    .repeats             = 0,
    .end_delay           = 0
};


/** @brief          PWM handler. do nothing. but not to be NULL for error prevent
 * 
 */
static void PWM_Handler(nrf_drv_pwm_evt_type_t event_type)
{
    switch (event_type)
    {
        case NRFX_PWM_EVT_FINISHED:
        break;
        
        case NRFX_PWM_EVT_END_SEQ0:
        break;

        case NRFX_PWM_EVT_END_SEQ1:
        break;

        case NRFX_PWM_EVT_STOPPED:
        break;
    
        default:
            // do nothing
        break;
    }
}


/** @brief          Initialize PWM driver
 *  @details        Initialize PWM driver for LED. Max value is 255(0xFF)(1byte). LED is active low.
 */
void Init_PWM_Driver(void)
{
    uint32_t err_code;

    nrf_drv_pwm_config_t pwm_config =
    {
        .output_pins =
        {
            USER_PWM_PIN_R,     // channel 0
            USER_PWM_PIN_G,     // channel 1
            USER_PWM_PIN_B,     // channel 2
            #if(USER_PWM_CHANNEL == 4)
            USER_PWM_PIN_W      // channel 3
            #endif
        },
        .irq_priority = APP_IRQ_PRIORITY_LOWEST,
        .base_clock   = NRF_PWM_CLK_1MHz,
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = 255,
        .load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
        .step_mode    = NRF_PWM_STEP_AUTO
    };

    err_code = nrf_drv_pwm_init(&m_pwm_bulb, &pwm_config, PWM_Handler);
    APP_ERROR_CHECK(err_code);

    pwm_values.channel_0 = 0|USER_PWM_POLARITY;       //R
    pwm_values.channel_1 = 0|USER_PWM_POLARITY;       //G
    pwm_values.channel_2 = 0|USER_PWM_POLARITY;       //B
    #if(USER_PWM_CHANNEL == 4)
    pwm_values.channel_3 = 0|USER_PWM_POLARITY;       //W
    #endif

    nrf_drv_pwm_simple_playback(&m_pwm_bulb, &pwm_seq, 1, NRF_DRV_PWM_FLAG_LOOP);
}


/** @brief          Set PWM LED value to each color channels. Bulb LED is Active Low.
 *                  
 */
void Set_PWM_Value(sColorRGBI_t rgbw_vlaue)
{
    sColorRGBW_t pwm_array;

    pwm_array = RGBI_to_RGBW(rgbw_vlaue);        
    
    pwm_values.channel_0 = pwm_array.R|USER_PWM_POLARITY;
    pwm_values.channel_1 = pwm_array.G|USER_PWM_POLARITY;
    pwm_values.channel_2 = pwm_array.B|USER_PWM_POLARITY;
    
    #if(USER_PWM_CHANNEL == 4)
    pwm_values.channel_3 = pwm_array.W|USER_PWM_POLARITY;
    #endif
}



void Stop_PWM(void)
{
    pwm_values.channel_0 = 0|USER_PWM_POLARITY;       //R
    pwm_values.channel_1 = 0|USER_PWM_POLARITY;       //G
    pwm_values.channel_2 = 0|USER_PWM_POLARITY;       //B
    #if(USER_PWM_CHANNEL == 4)
    pwm_values.channel_3 = 0|USER_PWM_POLARITY;       //W
    #endif

    nrfx_pwm_stop(&m_pwm_bulb, true);
}




//end of File

