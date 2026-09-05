/**
 * @file driver_adxl362_basic.h
 * @brief  none
 * @version 0.1
 * @author Alessandro Davi
 * @date 2026-09-04
 */

#ifndef DRIVER_ADXL362_BASIC_H
#define DRIVER_ADXL362_BASIC_H

#include "adxl362_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup adxl362_example_driver adxl362 example driver function
 * @brief    adxl362 example driver modules
 * @ingroup  adxl362_driver
 * @{
 */

/**
 * @brief adxl362 basic example default definition
 */
#define ADXL362_BASIC_DEFAULT_BANDWIDTH_ODR        ADXL362_BANDWIDTH_ODR_DIV_2        /**< bandwidth odr 1/2 */
#define ADXL362_BASIC_DEFAULT_NOISE_MODE           ADXL362_NOISE_MODE_NORMAL          /**< normal noise mode */
#define ADXL362_BASIC_DEFAULT_ODR                  ADXL362_ODR_12P5HZ                 /**< 12.5Hz */
#define ADXL362_BASIC_DEFAULT_RANGE                ADXL362_RANGE_2G                   /**< 2g */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t adxl362_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t adxl362_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *g pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t adxl362_basic_read(float g[3]);

/**
 * @brief      basic example read 8msb
 * @param[out] *g pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t adxl362_basic_read_8msb(float g[3]);

/**
 * @brief      basic example read temperature
 * @param[out] *temp pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t adxl362_basic_read_temperature(float *temp);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // DRIVER_ADXL362_BASIC_H