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
 * @file      main.c
 * @brief     main source file
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
#include "driver_apm2000_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];             /**< uart buffer */
volatile uint16_t g_len;        /**< uart buffer length */

/**
 * @brief     apm2000 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t apm2000(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"interface", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    apm2000_interface_t interface = APM2000_INTERFACE_IIC;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* interface */
            case 1 :
            {
                /* set the interface */
                if (strcmp("iic", optarg) == 0)
                {
                    interface = APM2000_INTERFACE_IIC;
                }
                else if (strcmp("uart", optarg) == 0)
                {
                    interface = APM2000_INTERFACE_UART;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 2 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* read test */
        if (apm2000_read_test(interface, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* init */
        res = apm2000_basic_init(interface);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 2000 ms */
        apm2000_interface_delay_ms(2000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            apm2000_pm_t pm;
            
            /* read data */
            res = apm2000_basic_read(&pm);
            if (res != 0)
            {
                (void)apm2000_basic_deinit();
                
                return 1;
            }
            
            /* print */
            apm2000_interface_debug_print("apm2000: %d/%d.\n", i + 1, times);
            apm2000_interface_debug_print("apm2000: pm1.0 is %d ug/m3.\n", pm.pm1p0_ug_m3);
            apm2000_interface_debug_print("apm2000: pm2.5 is %d ug/m3.\n", pm.pm2p5_ug_m3);
            apm2000_interface_debug_print("apm2000: pm10.0 is %d ug/m3.\n", pm.pm10_ug_m3);
            
            /* delay 2000 ms */
            apm2000_interface_delay_ms(2000);
        }
        
        /* deinit */
        (void)apm2000_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        apm2000_interface_debug_print("Usage:\n");
        apm2000_interface_debug_print("  apm2000 (-i | --information)\n");
        apm2000_interface_debug_print("  apm2000 (-h | --help)\n");
        apm2000_interface_debug_print("  apm2000 (-p | --port)\n");
        apm2000_interface_debug_print("  apm2000 (-t read | --test=read) [--interface=<iic | uart>] [--times=<num>]\n");
        apm2000_interface_debug_print("  apm2000 (-e read | --example=read) [--interface=<iic | uart>] [--times=<num>]\n");
        apm2000_interface_debug_print("\n");
        apm2000_interface_debug_print("Options:\n");
        apm2000_interface_debug_print("  -e <read>, --example=<read>         Run the driver example.\n");
        apm2000_interface_debug_print("  -h, --help                          Show the help.\n");
        apm2000_interface_debug_print("  -i, --information                   Show the chip information.\n");
        apm2000_interface_debug_print("      --interface=<iic | uart>        Set the chip interface.([default: iic])\n");
        apm2000_interface_debug_print("  -p, --port                          Display the pin connections of the current board.\n");
        apm2000_interface_debug_print("  -t <read>, --test=<read>            Run the driver test.\n");
        apm2000_interface_debug_print("      --times=<num>                   Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        apm2000_info_t info;
        
        /* print apm2000 info */
        apm2000_info(&info);
        apm2000_interface_debug_print("apm2000: chip is %s.\n", info.chip_name);
        apm2000_interface_debug_print("apm2000: manufacturer is %s.\n", info.manufacturer_name);
        apm2000_interface_debug_print("apm2000: interface is %s.\n", info.interface);
        apm2000_interface_debug_print("apm2000: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        apm2000_interface_debug_print("apm2000: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        apm2000_interface_debug_print("apm2000: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        apm2000_interface_debug_print("apm2000: max current is %0.2fmA.\n", info.max_current_ma);
        apm2000_interface_debug_print("apm2000: max temperature is %0.1fC.\n", info.temperature_max);
        apm2000_interface_debug_print("apm2000: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        apm2000_interface_debug_print("apm2000: IIC interface SCL connected to GPIOB PIN8.\n");
        apm2000_interface_debug_print("apm2000: IIC interface SDA connected to GPIOB PIN9.\n");
        apm2000_interface_debug_print("apm2000: UART interface TX connected to GPIOA PIN3.\n");
        apm2000_interface_debug_print("apm2000: UART interface RX connected to GPIOA PIN2.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register apm2000 function */
    shell_init();
    shell_register("apm2000", apm2000);
    uart_print("apm2000: welcome to libdriver apm2000.\n");

    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("apm2000: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("apm2000: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("apm2000: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("apm2000: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("apm2000: param is invalid.\n");
            }
            else
            {
                uart_print("apm2000: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
