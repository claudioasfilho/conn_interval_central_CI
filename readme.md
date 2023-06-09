# SoC - Central_AM

The Bluetooth example is a Central device that scans and connects to up to 32 peripheral devices which advertise a specific service **"CCCC"**. 

The Peripheral Device application can be found at: https://github.com/claudioasfilho/_32Con-EndNode412

Once it finds the device, it will subscribe to notifications.

By Pressing PB0 it will start the test, where the Peripheral nodes will send a send a substantial amount of data and after the TEST_TIMEOUT runs out, it will printout on the UART a report showing how much data was received from each connected node and its Upstream throughput.


 **Please note that if the Radio Board used is not the BRD4180A, it will be required to change the button port and pin definitions on app.c.**

The device outputs to the serial port with Baudrate of 115200 8-N-1 using ctsrts flow control .
Unix Screen invoking command: screen /dev/cu.usbmodem0004401694931 115200 ortsfl -rtsflow -ctsflow

**Other details:**

Hardware: EFR31MG21 - **BRD4180A**
https://www.silabs.com/documents/public/schematic-files/BRD4180A-hw-design-pkg.zip 
Compiler: GCC GNU ARM v10.2.1
**Gecko SDK Suite Version: 4.1.2**: Amazon 202012.00, Bluetooth 4.2.0, Bluetooth Mesh 3.0.2, EmberZNet 7.1.2.0, Flex 3.4.2.0, HomeKit 1.2.2.0, MCU 6.3.1.0, Matter Demo, Micrium OS Kernel 5.13.10, OpenThread 2.1.2.0 (GitHub-2ce3d3bf0), Platform 4.1.0.0, USB 1.0.0.0, Wi-SUN 1.3.2.0, Z-Wave SDK 7.18.2.0




## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

