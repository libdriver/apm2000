/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_apm2000.h
 * @brief     driver apm2000 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-07-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/07/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_APM2000_H
#define DRIVER_APM2000_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup apm2000_driver apm2000 driver function
 * @brief    apm2000 driver modules
 * @{
 */

/**
 * @addtogroup apm2000_basic_driver
 * @{
 */

/**
 * @brief apm2000 interface enumeration definition
 */
typedef enum
{
    APM2000_INTERFACE_IIC  = 0x00,       /**< iic interface */
    APM2000_INTERFACE_UART = 0x01,       /**< uart interface */
} apm2000_interface_t;

/**
 * @brief apm2000 handle structure definition
 */
typedef struct apm2000_handle_s
{
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    uint8_t (*iic_write_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write_address16 function address */
    uint8_t (*uart_init)(void);                                                                    /**< point to an uart_init function address */
    uint8_t (*uart_deinit)(void);                                                                  /**< point to an uart_deinit function address */
    uint16_t (*uart_read)(uint8_t *buf, uint16_t len);                                             /**< point to an uart_read function address */
    uint8_t (*uart_flush)(void);                                                                   /**< point to an uart_flush function address */
    uint8_t (*uart_write)(uint8_t *buf, uint16_t len);                                             /**< point to an uart_write function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint8_t inited;                                                                                /**< inited flag */
    uint8_t iic_uart;                                                                              /**< iic uart */
    uint8_t buf[255 + 5];                                                                          /**< inner buffer */
} apm2000_handle_t;

/**
 * @brief apm2000 pm structure definition
 */
typedef struct apm2000_pm_s
{
    uint16_t pm1p0_ug_m3;        /**< mass concentration pm1.0 [μg/m3] */
    uint16_t pm2p5_ug_m3;        /**< mass concentration pm2.5 [μg/m3] */
    uint16_t pm10_ug_m3;         /**< mass concentration pm10 [μg/m3] */
} apm2000_pm_t;

/**
 * @brief apm2000 information structure definition
 */
typedef struct apm2000_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[16];                /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} apm2000_info_t;

/**
 * @}
 */

/**
 * @defgroup apm2000_link_driver apm2000 link driver function
 * @brief    apm2000 link driver modules
 * @ingroup  apm2000_driver
 * @{
 */

/**
 * @brief     initialize apm2000_handle_t structure
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] STRUCTURE apm2000_handle_t
 * @note      none
 */
#define DRIVER_APM2000_LINK_INIT(HANDLE, STRUCTURE)              memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link uart_init function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an uart_init function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_UART_INIT(HANDLE, FUC)              (HANDLE)->uart_init = FUC

/**
 * @brief     link uart_deinit function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an uart_deinit function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_UART_DEINIT(HANDLE, FUC)            (HANDLE)->uart_deinit = FUC

/**
 * @brief     link uart_read function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an uart_read function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_UART_READ(HANDLE, FUC)              (HANDLE)->uart_read = FUC

/**
 * @brief     link uart_write function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an uart_write function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_UART_WRITE(HANDLE, FUC)             (HANDLE)->uart_write = FUC

/**
 * @brief     link uart_flush function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an uart_flush function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_UART_FLUSH(HANDLE, FUC)             (HANDLE)->uart_flush = FUC

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_IIC_INIT(HANDLE, FUC)               (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_IIC_DEINIT(HANDLE, FUC)             (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_address16 function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an iic_write_address16 function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_IIC_WRITE_ADDRESS16(HANDLE, FUC)    (HANDLE)->iic_write_address16 = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)     (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_DELAY_MS(HANDLE, FUC)               (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an apm2000 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_APM2000_LINK_DEBUG_PRINT(HANDLE, FUC)            (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup apm2000_basic_driver apm2000 basic driver function
 * @brief    apm2000 basic driver modules
 * @ingroup  apm2000_driver
 * @{
 */

/**
 * @brief      get chip information
 * @param[out] *info pointer to an apm2000 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t apm2000_info(apm2000_info_t *info);

/**
 * @brief     set the chip interface
 * @param[in] *handle pointer to an apm2000 handle structure
 * @param[in] interface chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t apm2000_set_interface(apm2000_handle_t *handle, apm2000_interface_t interface);

/**
 * @brief      get the chip interface
 * @param[in]  *handle pointer to an apm2000 handle structure
 * @param[out] *interface pointer to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t apm2000_get_interface(apm2000_handle_t *handle, apm2000_interface_t *interface);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an apm2000 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or uart initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t apm2000_init(apm2000_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an apm2000 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or uart deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apm2000_deinit(apm2000_handle_t *handle);

/**
 * @brief      read the result
 * @param[in]  *handle pointer to an apm2000 handle structure
 * @param[out] *pm pointer to an apm2000 pm structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc check failed
 * @note       none
 */
uint8_t apm2000_read(apm2000_handle_t *handle, apm2000_pm_t *pm);

/**
 * @brief      read pm2.5
 * @param[in]  *handle pointer to an apm2000 handle structure
 * @param[out] *pm2p5_ug_m3 pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 iic can't use this function
 * @note       iic can't use this function
 */
uint8_t apm2000_read_pm2p5(apm2000_handle_t *handle, uint16_t *pm2p5_ug_m3);

/**
 * @brief     start the measurement
 * @param[in] *handle pointer to an apm2000 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start measurement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 uart can't use this function
 * @note      uart can't use this function
 */
uint8_t apm2000_start_measurement(apm2000_handle_t *handle);

/**
 * @brief     stop the measurement
 * @param[in] *handle pointer to an apm2000 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop measurement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 uart can't use this function
 * @note      uart can't use this function
 */
uint8_t apm2000_stop_measurement(apm2000_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup apm2000_extern_driver apm2000 extern driver function
 * @brief    apm2000 extern driver modules
 * @ingroup  apm2000_driver
 * @{
 */

/**
 * @brief     set the chip register with iic interface
 * @param[in] *handle pointer to an apm2000 handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apm2000_set_reg_iic(apm2000_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register with iic interface
 * @param[in]  *handle pointer to an apm2000 handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t apm2000_get_reg_iic(apm2000_handle_t *handle, uint16_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      set and get the chip register with uart interface
 * @param[in]  *handle pointer to an apm2000 handle structure
 * @param[in]  *input pointer to an input buffer
 * @param[in]  in_len input length
 * @param[out] *output pointer to an output buffer
 * @param[in]  out_len output length
 * @return     status code
 *             - 0 success
 *             - 1 write read failed
 * @note       none
 */
uint8_t apm2000_set_get_reg_uart(apm2000_handle_t *handle, uint8_t *input, uint16_t in_len, uint8_t *output, uint16_t out_len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
