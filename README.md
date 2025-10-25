[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APM2000

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apm2000/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

APM2000 is a digital particle detection sensor designed based on the principle of laser scattering, which can detect particle concentration in real time. APM2000 can test particles with a particle size range of 0.3~10um, provide multiple different digital output interfaces, and have self calibration function when turned on. It has good stability, small size, and is easy to integrate.

LibDriver APM2000 is a full-featured driver for APM2000, launched by LibDriver.It provides PM1.0, PM2.5, PM10 reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver APM2000 source files.

/interface includes LibDriver APM2000 IIC, UART platform independent template.

/test includes LibDriver APM2000 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver APM2000 sample code.

/doc includes LibDriver APM2000 offline document.

/datasheet includes APM2000 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC, UART platform independent template and finish your platform IIC, UART driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_apm2000_basic.h"

uint8_t res;
uint32_t i;

/* init */
res = apm2000_basic_init(APM2000_INTERFACE_IIC);
if (res != 0)
{
    return 1;
}

...
    
/* delay 2000 ms */
apm2000_interface_delay_ms(2000);

/* loop */
for (i = 0; i < 3; i++)
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
    apm2000_interface_debug_print("apm2000: %d/%d.\n", i + 1, 3);
    apm2000_interface_debug_print("apm2000: pm1.0 is %d ug/m3.\n", pm.pm1p0_ug_m3);
    apm2000_interface_debug_print("apm2000: pm2.5 is %d ug/m3.\n", pm.pm2p5_ug_m3);
    apm2000_interface_debug_print("apm2000: pm10.0 is %d ug/m3.\n", pm.pm10_ug_m3);

    /* delay 2000 ms */
    apm2000_interface_delay_ms(2000);
    
    ...
}

...
    
/* deinit */
(void)apm2000_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/apm2000/index.html](https://www.libdriver.com/docs/apm2000/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.