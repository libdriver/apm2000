### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

UART2 Pin:  TX/RX PA2/PA3.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. APM2000

#### 3.1 Command Instruction

1. Show apm2000 chip and driver information.

   ```shell
   apm2000 (-i | --information)
   ```

2. Show apm2000 help.

   ```shell
   apm2000 (-h | --help)
   ```

3. Show apm2000 pin connections of the current board.

   ```shell
   apm2000 (-p | --port)
   ```

4. Run apm2000 read test, num means the test times.

   ```shell
   apm2000 (-t read | --test=read) [--interface=<iic | uart>] [--times=<num>]
   ```

5. Run apm2000 basic read function, num means the read times.

   ```shell
   apm2000 (-e read | --example=read) [--interface=<iic | uart>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
apm2000 -i

apm2000: chip is ASAIR APM2000.
apm2000: manufacturer is ASAIR.
apm2000: interface is UART IIC.
apm2000: driver version is 1.0.
apm2000: min supply voltage is 4.8V.
apm2000: max supply voltage is 5.2V.
apm2000: max current is 100.00mA.
apm2000: max temperature is 50.0C.
apm2000: min temperature is -10.0C.
```

```shell
apm2000 -p

apm2000: IIC interface SCL connected to GPIOB PIN8.
apm2000: IIC interface SDA connected to GPIOB PIN9.
apm2000: UART interface TX connected to GPIOA PIN3.
apm2000: UART interface RX connected to GPIOA PIN2.
```

```shell
apm2000 -t read --interface=iic --times=3

apm2000: chip is ASAIR APM2000.
apm2000: manufacturer is ASAIR.
apm2000: interface is UART IIC.
apm2000: driver version is 1.0.
apm2000: min supply voltage is 4.8V.
apm2000: max supply voltage is 5.2V.
apm2000: max current is 100.00mA.
apm2000: max temperature is 50.0C.
apm2000: min temperature is -10.0C.
apm2000: start read test.
apm2000: pm1.0 is 13 ug/m3.
apm2000: pm2.5 is 15 ug/m3.
apm2000: pm10.0 is 15 ug/m3.
apm2000: pm1.0 is 13 ug/m3.
apm2000: pm2.5 is 15 ug/m3.
apm2000: pm10.0 is 15 ug/m3.
apm2000: pm1.0 is 13 ug/m3.
apm2000: pm2.5 is 15 ug/m3.
apm2000: pm10.0 is 15 ug/m3.
apm2000: finish read test.
```

```shell
apm2000 -e read --interface=iic --times=3

apm2000: 1/3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 18 ug/m3.
apm2000: pm10.0 is 18 ug/m3.
apm2000: 2/3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 18 ug/m3.
apm2000: pm10.0 is 18 ug/m3.
apm2000: 3/3.
apm2000: pm1.0 is 13 ug/m3.
apm2000: pm2.5 is 15 ug/m3.
apm2000: pm10.0 is 16 ug/m3.
```

```shell
apm2000 -h

Usage:
  apm2000 (-i | --information)
  apm2000 (-h | --help)
  apm2000 (-p | --port)
  apm2000 (-t read | --test=read) [--interface=<iic | uart>] [--times=<num>]
  apm2000 (-e read | --example=read) [--interface=<iic | uart>] [--times=<num>]

Options:
  -e <read>, --example=<read>         Run the driver example.
  -h, --help                          Show the help.
  -i, --information                   Show the chip information.
      --interface=<iic | uart>        Set the chip interface.([default: iic])
  -p, --port                          Display the pin connections of the current board.
  -t <read>, --test=<read>            Run the driver test.
      --times=<num>                   Set the running times.([default: 3])
```

