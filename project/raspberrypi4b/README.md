### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

UART Pin: TX/RX GPIO14/GPIO15.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```
#### 2.2 Configuration

Enable serial port.

Disable serial console.

#### 2.3 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.4 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(apm2000 REQUIRED)
```

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
./apm2000 -i

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
./apm2000 -p

apm2000: IIC interface SCL connected to GPIO3(BCM).
apm2000: IIC interface SDA connected to GPIO2(BCM).
apm2000: UART interface TX connected to GPIO15(BCM).
apm2000: UART interface RX connected to GPIO14(BCM).
```

```shell
./apm2000 -t read --interface=uart --times=3

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
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm10.0 is 17 ug/m3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm10.0 is 17 ug/m3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm10.0 is 17 ug/m3.
apm2000: uart read pm2p5 test.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm2.5 is 18 ug/m3.
apm2000: finish read test.
```

```shell
./apm2000 -e read --interface=uart --times=3

apm2000: 1/3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm10.0 is 18 ug/m3.
apm2000: 2/3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm10.0 is 18 ug/m3.
apm2000: 3/3.
apm2000: pm1.0 is 16 ug/m3.
apm2000: pm2.5 is 17 ug/m3.
apm2000: pm10.0 is 18 ug/m3.
```

```shell
./apm2000 -h

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
