[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APM2000

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apm2000/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

APM2000是一款基於雷射散射原理設計的數字式顆粒物檢測感測器，可實时檢測顆粒物濃度。 APM2000可測試顆粒物的粒徑範圍是0.3~10um，能提供多種不同的數位輸出介面，具備開機自校準功能。 具有良好的穩定性，體積小，便於集成。

LibDriver APM2000是LibDriver推出的APM2000全功能驅動，該驅動提供PM1.0，PM2.5，PM10讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver APM2000的源文件。

/interface目錄包含了LibDriver APM2000與平台無關的IIC, UART總線模板。

/test目錄包含了LibDriver APM2000驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver APM2000編程範例。

/doc目錄包含了LibDriver APM2000離線文檔。

/datasheet目錄包含了APM2000數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC, UART總線模板，完成指定平台的IIC, UART總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/apm2000/index.html](https://www.libdriver.com/docs/apm2000/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
