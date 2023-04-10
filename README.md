# CH552E USB Knob - Rotary Encoder with USB Interface
The USB Knob is a versatile device that combines the functionality of a rotary encoder with the convenience of a USB interface. It is based on either the CH552E or CH554E microcontroller and is equipped with addressable LEDs, commonly known as NeoPixels. The unique combination of these components makes the USB Knob an ideal choice for a wide range of applications, including volume control for PCs.

One of the standout features of the USB Knob is that it requires no driver installation, making it incredibly easy to use. The device acts as a HID custom keyboard, meaning that it can be recognized and utilized by most computers without the need for additional software.

The accompanying example firmware for the USB Knob further streamlines the process of using this device, providing users with a simple and effective means of controlling the volume on their computer. The code implements a volume control knob that can be used to adjust the volume levels of a PC, making it easy to regulate the audio output without having to navigate through menus or use complicated software.

![USB_Knob_pic1.jpg](https://raw.githubusercontent.com/wagiminator/CH552-USB-Knob/main/documentation/USB_Knob_pic1.jpg)

# Hardware
## Schematic
![USB_Knob_wiring.png](https://raw.githubusercontent.com/wagiminator/CH552-USB-Knob/main/documentation/USB_Knob_wiring.png)

## CH552E 8-bit USB Device Microcontroller
The CH552E is a low-cost, enhanced E8051 core microcontroller compatible with the MCS51 instruction set. It has an integrated USB 2.0 controller with full-speed data transfer (12 Mbit/s) and supports up to 64 byte data packets with integrated FIFO and direct memory access (DMA). The CH552E has a factory built-in bootloader so firmware can be uploaded directly via USB without the need for an additional programming device.

![USB_Knob_pic2.jpg](https://raw.githubusercontent.com/wagiminator/CH552-USB-Knob/main/documentation/USB_Knob_pic2.jpg)

# Compiling and Installing Firmware
## Preparing the CH55x Bootloader
### Installing Drivers for the CH55x Bootloader
On Linux you do not need to install a driver. However, by default Linux will not expose enough permission to upload your code with the USB bootloader. In order to fix this, open a terminal and run the following commands:

```
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="4348", ATTR{idProduct}=="55e0", MODE="666"' | sudo tee /etc/udev/rules.d/99-ch55x.rules
sudo service udev restart
```

For Windows, you need the [CH372 driver](http://www.wch-ic.com/downloads/CH372DRV_EXE.html). Alternatively, you can also use the [Zadig Tool](https://zadig.akeo.ie/) to install the correct driver. Here, click "Options" and "List All Devices" to select the USB module, and then install the libusb-win32 driver. To do this, the board must be connected and the CH55x must be in bootloader mode.

### Entering CH55x Bootloader Mode
A brand new chip starts automatically in bootloader mode as soon as it is connected to the PC via USB. Once firmware has been uploaded, the bootloader must be started manually for new uploads. To do this, the board must first be disconnected from the USB port and all voltage sources. Now press the BOOT button and keep it pressed while reconnecting the board to the USB port of your PC. The chip now starts again in bootloader mode, the BOOT button can be released and new firmware can be uploaded within the next couple of seconds.

Once the USB Knob firmware is installed, the bootloader can also be entered by holding down the rotary encoder switch while connecting the device to the USB port. In this way, the case does not have to be opened when new firmware is to be installed. The NeoPixels will then light up white as long as the device is in bootloader mode (approx. 10 seconds).

## Compiling and Uploading using the makefile
### Installing SDCC Toolchain for CH55x
Install the [SDCC Compiler](https://sdcc.sourceforge.net/). In order for the programming tool to work, Python3 must be installed on your system. To do this, follow these [instructions](https://www.pythontutorial.net/getting-started/install-python/). In addition [pyusb](https://github.com/pyusb/pyusb) must be installed. On Linux (Debian-based), all of this can be done with the following commands:

```
sudo apt install build-essential sdcc python3 python3-pip
sudo pip install pyusb
```

### Compiling and Uploading Firmware
- Open a terminal.
- Navigate to the folder with the makefile. 
- Connect the board and make sure the CH55x is in bootloader mode. 
- Run ```make flash``` to compile and upload the firmware. 
- If you don't want to compile the firmware yourself, you can also upload the precompiled binary. To do this, just run ```python3 ./tools/chprog.py firmware.bin```.

## Compiling and Uploading using the Arduino IDE
### Installing the Arduino IDE and CH55xduino
Install the [Arduino IDE](https://www.arduino.cc/en/software) if you haven't already. Install the [CH55xduino](https://github.com/DeqingSun/ch55xduino) package by following the instructions on the website.

### Compiling and Uploading Firmware
- Open the .ino file in the Arduino IDE.
- Go to **Tools -> Board -> CH55x Boards** and select **CH552 Board**.
- Go to **Tools** and choose the following board options:
  - **Clock Source:**   16 MHz (internal)
  - **Upload Method:**  USB
  - **USB Settings:**   USER CODE /w 266B USB RAM
- Connect the board and make sure the CH55x is in bootloader mode. 
- Click **Upload**.

# References, Links and Notes
1. [EasyEDA Design Files](https://oshwlab.com/wagiminator)
2. [CH551/552 Datasheet](http://www.wch-ic.com/downloads/CH552DS1_PDF.html)
3. [SDCC Compiler](https://sdcc.sourceforge.net/)
4. [ATtiny85 TinyKnob](https://github.com/wagiminator/ATtiny85-TinyKnob)

![USB_Knob_pic3.jpg](https://raw.githubusercontent.com/wagiminator/CH552-USB-Knob/main/documentation/USB_Knob_pic3.jpg)
![USB_Knob_pic4.jpg](https://raw.githubusercontent.com/wagiminator/CH552-USB-Knob/main/documentation/USB_Knob_pic4.jpg)

# License
![license.png](https://i.creativecommons.org/l/by-sa/3.0/88x31.png)

This work is licensed under Creative Commons Attribution-ShareAlike 3.0 Unported License. 
(http://creativecommons.org/licenses/by-sa/3.0/)
