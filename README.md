# USB HID Tool #

This is a command line tool for accessing USB HID devices. It assumes that the device will respond to a received packet by immediately sending a response.

### How to use it ###

Command line arguments provide the VID and PID and the contents of the 64 byte packet sent to the device. The response is 'NULL' is no device is connected, 'ERROR: message' if something went wrong trying to connect to or read from the device, or the 64 byte packet returned from the device. For example, with the AudioMoth device:

```
> ./usbhidtool 0x10C4 0x0002 0x00 0x01
01 2b 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ###### Your 
```

From Node.js or Python the command line tool can be called as a child process.

### Linux ###

The executable will work as is on macOS and Windows. However, Linux prevents USB HID devices from being writable by default. This can be fixed by adding an additional rule in /lib/udev/rules.d/. For AudioMoth, the following additional rule file, called 99-audiomoth.rules, is used. The content of which is:

```
SUBSYSTEM=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="0002", MODE="0666"
```

### Building ###

On macOS use the Xcode project to build the binary. After archiving, the resulting executable must be manually moved to the correct folder.

On Linux use gcc to build the binary by running build.sh. This will copy the executable to the correct folder. Or compile manually. 

```
> gcc -Wall -std=c99 -I/usr/include/libusb-1.0 -I.. -o usbhidtool ../main.c hid.c -lusb-1.0 -lrt -lpthread
```

The libusb development library must be installed.

```
> sudo apt-get install libusb-1.0-0-dev
```

On Windows use the Microsoft Visual C++ Build Tools on the command line by running running build.bat or build32.bat. This will copy the executable to the correct folder. 

Or compile manually. 

```
> cl /I .. ../main.c hid.c /link /out:usbhidtool.exe SetupAPI.lib 
```

Note that to build the correct version you should run the command in the correct environment. Use the 'x64 Native Tools Command Prompt' to build the 64-bit binary on a 64-bit machine, and the 'x64_x86 Cross Tools Command Prompt' to build the 32-bit binary on a 64-bit machine.
