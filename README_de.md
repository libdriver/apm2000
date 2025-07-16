[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver APM2000
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/apm2000/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

APM2000 ist ein digitaler Partikelsensor, der auf dem Prinzip der Laserstreuung basiert und die Partikelkonzentration in Echtzeit erfassen kann. APM2000 kann Partikel mit einem Partikelgrößenbereich von 0,3 bis 10 µm testen, bietet mehrere digitale Ausgangsschnittstellen und verfügt nach dem Einschalten über eine Selbstkalibrierungsfunktion. Er zeichnet sich durch hohe Stabilität, geringe Größe und einfache Integration aus.

LibDriver APM2000 ist ein vollfunktionaler Treiber für APM2000, der von LibDriver veröffentlicht wurde. Er bietet unter anderem die Möglichkeit, PM1.0-, PM2.5- und PM10-Emissionen zu messen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver APM2000-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver APM2000 IIC, UART.

/test enthält den Testcode des LibDriver APM2000-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver APM2000-Beispielcode.

/doc enthält das LibDriver APM2000-Offlinedokument.

/Datenblatt enthält APM2000-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC, UART-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC, UART-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/apm2000/index.html](https://www.libdriver.com/docs/apm2000/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.