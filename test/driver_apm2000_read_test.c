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
 * @file      driver_apm2000_read_test.c
 * @brief     driver apm2000 read test source file
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

#include "driver_apm2000_read_test.h"

static apm2000_handle_t gs_handle;        /**< apm2000 handle */

/**
 * @brief     read test
 * @param[in] interface chip interface
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t apm2000_read_test(apm2000_interface_t interface, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    apm2000_info_t info;
    apm2000_pm_t pm;
    
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
    
    /* get information */
    res = apm2000_info(&info);
    if (res != 0)
    {
        apm2000_interface_debug_print("apm2000: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        apm2000_interface_debug_print("apm2000: chip is %s.\n", info.chip_name);
        apm2000_interface_debug_print("apm2000: manufacturer is %s.\n", info.manufacturer_name);
        apm2000_interface_debug_print("apm2000: interface is %s.\n", info.interface);
        apm2000_interface_debug_print("apm2000: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        apm2000_interface_debug_print("apm2000: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        apm2000_interface_debug_print("apm2000: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        apm2000_interface_debug_print("apm2000: max current is %0.2fmA.\n", info.max_current_ma);
        apm2000_interface_debug_print("apm2000: max temperature is %0.1fC.\n", info.temperature_max);
        apm2000_interface_debug_print("apm2000: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    apm2000_interface_debug_print("apm2000: start read test.\n");
    
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
    
    /* delay 2000 ms */
    apm2000_interface_delay_ms(2000);
    
    for (i = 0; i < times; i++)
    {
        res = apm2000_read(&gs_handle, &pm);
        if (res != 0)
        {
            apm2000_interface_debug_print("apm2000: read failed.\n");
            (void)apm2000_deinit(&gs_handle);
            
            return 1;
        }
        apm2000_interface_debug_print("apm2000: pm1.0 is %d ug/m3.\n", pm.pm1p0_ug_m3);
        apm2000_interface_debug_print("apm2000: pm2.5 is %d ug/m3.\n", pm.pm2p5_ug_m3);
        apm2000_interface_debug_print("apm2000: pm10.0 is %d ug/m3.\n", pm.pm10_ug_m3);
        
        /* delay 2000 ms */
        apm2000_interface_delay_ms(2000);
    }
    
    /* uart */
    if (interface == APM2000_INTERFACE_UART)
    {
        /* uart read pm2p5 test */
        apm2000_interface_debug_print("apm2000: uart read pm2p5 test.\n");
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            uint16_t pm2p5_ug_m3;
            
            res = apm2000_read_pm2p5(&gs_handle, &pm2p5_ug_m3);
            if (res != 0)
            {
                apm2000_interface_debug_print("apm2000: read pm2p5 failed.\n");
                (void)apm2000_deinit(&gs_handle);
                
                return 1;
            }
            apm2000_interface_debug_print("apm2000: pm2.5 is %d ug/m3.\n", pm2p5_ug_m3);
            
            /* delay 2000 ms */
            apm2000_interface_delay_ms(2000);
        }
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
    
    /* finish read test */
    apm2000_interface_debug_print("apm2000: finish read test.\n");
    (void)apm2000_deinit(&gs_handle);
    
    return 0;
}
