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
 * @file      driver_apm2000_basic.c
 * @brief     driver apm2000 basic source file
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

#include "driver_apm2000_basic.h"

static apm2000_handle_t gs_handle;        /**< apm2000 handle */

/**
 * @brief     basic example init
 * @param[in] interface chip interface
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t apm2000_basic_init(apm2000_interface_t interface)
{
    uint8_t res;
    
    /* link functions */
    DRIVER_APM2000_LINK_INIT(&gs_handle, apm2000_handle_t);
    DRIVER_APM2000_LINK_UART_INIT(&gs_handle, apm2000_interface_uart_init);
    DRIVER_APM2000_LINK_UART_DEINIT(&gs_handle, apm2000_interface_uart_deinit);
    DRIVER_APM2000_LINK_UART_READ(&gs_handle, apm2000_interface_uart_read);
    DRIVER_APM2000_LINK_UART_WRITE(&gs_handle, apm2000_interface_uart_write);
    DRIVER_APM2000_LINK_UART_FLUSH(&gs_handle, apm2000_interface_uart_flush);
    DRIVER_APM2000_LINK_IIC_INIT(&gs_handle, apm2000_interface_iic_init);
    DRIVER_APM2000_LINK_IIC_DEINIT(&gs_handle, apm2000_interface_iic_deinit);
    DRIVER_APM2000_LINK_IIC_WRITE_ADDRESS16(&gs_handle, apm2000_interface_iic_write_address16);
    DRIVER_APM2000_LINK_IIC_READ_ADDRESS16(&gs_handle, apm2000_interface_iic_read_address16);
    DRIVER_APM2000_LINK_DELAY_MS(&gs_handle, apm2000_interface_delay_ms);
    DRIVER_APM2000_LINK_DEBUG_PRINT(&gs_handle, apm2000_interface_debug_print);
    
    /* set the interface */
    res = apm2000_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        apm2000_interface_debug_print("apm2000: set interface failed.\n");
    
        return 1;
    }
    
    /* init the chip */
    res = apm2000_init(&gs_handle);
    if (res != 0)
    {
        apm2000_interface_debug_print("apm2000: init failed.\n");
    
        return 1;
    }
    
    if (interface == APM2000_INTERFACE_IIC)
    {
        /* start measurement */
        res = apm2000_start_measurement(&gs_handle);
        if (res != 0)
        {
            apm2000_interface_debug_print("apm2000: start measurement failed.\n");
            (void)apm2000_deinit(&gs_handle);
            
            return 1;
        }
    }

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t apm2000_basic_deinit(void)
{
    uint8_t res;
    apm2000_interface_t interface;
    
    /* get interface */
    res = apm2000_get_interface(&gs_handle, &interface);
    if (res != 0)
    {
        return 1;
    }
    
    if (interface == APM2000_INTERFACE_IIC)
    {
        /* stop measurement */
        res = apm2000_stop_measurement(&gs_handle);
        if (res != 0)
        {
            return 1;
        }
    }
    
    /* deinit */
    res = apm2000_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *pm pointer to a apm2000_pm_t structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t apm2000_basic_read(apm2000_pm_t *pm)
{
    uint8_t res;
    
    /* read data */
    res = apm2000_read(&gs_handle, pm);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
