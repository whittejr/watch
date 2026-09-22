/**
* @file    bsp.c
* @brief   none
* @version 0.1.0
* @author  Alessandro Davi
* @date    2026-09-01
*/
#include "adxl362.h"
#include "driver_ssd1306.h"
#include "qpc.h"
#include "bsp.h"
#include "app.h"

#include "clock.h"
#include "driver_ssd1306_basic.h"
#include "driver_adxl362_basic.h"
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "uart.h"
#include <string.h>



static adxl362_handle_t adxl_handle;

// GERAL
void bsp_init(void) {
    clock_config();
    gpio_init();
    i2c_init();
    spi_init();
    uart_init();
    rtc_init();
    bsp_display_init_ssd1306();
    bsp_accel_init();
}

// ACELEROMETRO
uint8_t bsp_accel_init(void) {
    uint8_t res;
    
    /* link interface function */
    DRIVER_ADXL362_LINK_INIT(&adxl_handle, adxl362_handle_t);
    DRIVER_ADXL362_LINK_SPI_INIT(&adxl_handle, adxl362_interface_spi_init);
    DRIVER_ADXL362_LINK_SPI_DEINIT(&adxl_handle, adxl362_interface_spi_deinit);
    DRIVER_ADXL362_LINK_SPI_READ(&adxl_handle, adxl362_interface_spi_read);
    DRIVER_ADXL362_LINK_SPI_READ_ADDRESS16(&adxl_handle, adxl362_interface_spi_read_address16);
    DRIVER_ADXL362_LINK_SPI_WRITE_ADDRESS16(&adxl_handle, adxl362_interface_spi_write_address16);
    DRIVER_ADXL362_LINK_DELAY_MS(&adxl_handle, adxl362_interface_delay_ms);
    DRIVER_ADXL362_LINK_DEBUG_PRINT(&adxl_handle, adxl362_interface_debug_print);
    DRIVER_ADXL362_LINK_RECEIVE_CALLBACK(&adxl_handle, adxl362_interface_receive_callback);
    
    /* init the adxl362 */
    res = adxl362_init(&adxl_handle);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: init failed.\n");
       
        return 1;
    }
    
    /* disable fifo temperature */
    res = adxl362_set_fifo_temperature(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set fifo temperature failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo */
    res = adxl362_set_fifo_mode(&adxl_handle, ADXL362_FIFO_MODE_DISABLE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set fifo mode failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set fifo sample 0 */
    res = adxl362_set_fifo_sample(&adxl_handle, 0);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set fifo sample failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set interrupt pin1 active level low */
    res = adxl362_set_interrupt_pin1_active_level(&adxl_handle, ADXL362_INTERRUPT_PIN_LOW);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 active level failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable awake map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_AWAKE, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable inact map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_INACT, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable act map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_ACT, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo overrun map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_FIFO_OVERRUN, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo watermark map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_FIFO_WATERMARK, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo ready map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_FIFO_READY, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable data ready map */
    res = adxl362_set_interrupt_pin1_map(&adxl_handle, ADXL362_INTERRUPT_MAP_DATA_READY, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set interrupt pin2 active level low */
    res = adxl362_set_interrupt_pin2_active_level(&adxl_handle, ADXL362_INTERRUPT_PIN_LOW);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 active level failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable awake map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_AWAKE, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable inact map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_INACT, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable act map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_ACT, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo overrun map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_FIFO_OVERRUN, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo watermark map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_FIFO_WATERMARK, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable fifo ready map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_FIFO_READY, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable data ready map */
    res = adxl362_set_interrupt_pin2_map(&adxl_handle, ADXL362_INTERRUPT_MAP_DATA_READY, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 map failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set default bandwidth */
    res = adxl362_set_bandwidth(&adxl_handle, ADXL362_BASIC_DEFAULT_BANDWIDTH_ODR);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set bandwidth failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set default noise mode */
    res = adxl362_set_noise_mode(&adxl_handle, ADXL362_BASIC_DEFAULT_NOISE_MODE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set noise mode failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable wake up */
    res = adxl362_set_wake_up(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set wake up failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable auto sleep */
    res = adxl362_set_auto_sleep(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set auto sleep failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable interrupt pin2 as external sampling trigger */
    res = adxl362_set_interrupt_pin2_as_external_sampling_trigger(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin2 as external sampling trigger failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable interrupt pin1 as external clock */
    res = adxl362_set_interrupt_pin1_as_external_clock(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set interrupt pin1 as external clock failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set activity threshold 0x0000 */
    res = adxl362_set_activity_threshold(&adxl_handle, 0x0000);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set activity threshold failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set activity time 0x00 */
    res = adxl362_set_activity_time(&adxl_handle, 0x00);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set activity time failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set inactivity threshold 0x0000 */
    res = adxl362_set_inactivity_threshold(&adxl_handle, 0x0000);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set inactivity threshold failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set inactivity time 0x0000 */
    res = adxl362_set_inactivity_time(&adxl_handle, 0x0000);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set inactivity time failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set detect link mode */
    res = adxl362_set_detect_mode(&adxl_handle, ADXL362_DETECT_MODE_LINK);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set detect mode failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set inactivity detect trigger */
    res = adxl362_set_inactivity_detect_trigger(&adxl_handle, ADXL362_DETECT_TRIGGER_REFERENCED);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set inactivity detect trigger failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set activity detect trigger */
    res = adxl362_set_activity_detect_trigger(&adxl_handle, ADXL362_DETECT_TRIGGER_REFERENCED);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set activity detect trigger failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable inactivity */
    res = adxl362_set_inactivity(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set inactivity failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable activity */
    res = adxl362_set_activity(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set activity failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* disable self test */
    res = adxl362_set_self_test(&adxl_handle, ADXL362_BOOL_FALSE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set self test failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set default odr */
    res = adxl362_set_odr(&adxl_handle, ADXL362_BASIC_DEFAULT_ODR);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set odr failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* set default range */
    res = adxl362_set_range(&adxl_handle, ADXL362_BASIC_DEFAULT_RANGE);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set range failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    /* start measurement */
    res = adxl362_set_mode(&adxl_handle, ADXL362_MODE_MEASUREMENT);
    if (res != 0)
    {
        adxl362_interface_debug_print("adxl362: set mode failed.\n");
        (void)adxl362_deinit(&adxl_handle);
        
        return 1;
    }
    
    return 0;
}

uint8_t bsp_accel_get_xyz(bsp_accel_raw_t *raw_out) {
    if (!raw_out) return 1;
    int16_t raw[3];
    float g[3];

    if (adxl362_read(&adxl_handle, raw, g) == 0) {
        raw_out->x = raw[0];
        raw_out->y = raw[1];
        raw_out->z = raw[2];
        return 0;
    }
    return 1;
}

void bsp_accel_fall_detection(void) {
}

// DISPLAY
void bsp_display_init_ssd1306(void) {
    ssd1306_basic_init(0x00, 0x78);
    ssd1306_basic_display_on();
}
void bsp_display_write_string_ssd1306(uint8_t x, uint8_t y, char *texto) {
    ssd1306_basic_string(x, y, texto, (uint16_t)strlen(texto), 1, SSD1306_FONT_12);
}
void bsp_display_clear_ssd1306(void) {
    ssd1306_basic_clear();
}

// TEMPO
void bsp_get_time(bsp_datetime_t *dt) {
    if (!dt) return;
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    rtc_get_time(&sTime, &sDate);

    dt->hour   = sTime.Hours;
    dt->minute = sTime.Minutes;
    dt->second = sTime.Seconds;
    dt->day    = sDate.Date;
    dt->month  = sDate.Month;
    dt->year   = sDate.Year;
}

void bsp_set_time(const bsp_datetime_t *dt) {
    if (!dt) return;
    rtc_set_time(dt->hour, dt->minute, dt->second);
}
