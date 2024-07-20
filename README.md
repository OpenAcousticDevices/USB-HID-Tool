# USB HID Tool #

This is a command line tool for accessing USB HID devices. It assumes that the device will respond to a received packet by immediately sending a response.

## How to use it ##

Command line arguments provide the VID and PID and the contents of the 64 byte packet sent to the device. The response is 'NULL' is no device is connected, 'ERROR: message' if something went wrong trying to connect to or read from the device, or the 64 byte packet returned from the device. For example, with the AudioMoth device:

```
> ./usbhidtool 0x10C4 0x0002 0x00 0x01
01 2b 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  
```

From Node.js or Python the command line tool can be called as a child process.

### Linux ###

By default, Linux prevents writing to certain types of USB devices such as the AudioMoth. To use this application you must first navigate to `/lib/udev/rules.d/` and create a new file (or edit the existing file) with the name `99-audiomoth.rules`:

```
> cd /lib/udev/rules.d/
> sudo gedit 99-audiomoth.rules
```

Then add the following text:

```
SUBSYSTEM=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="0002", MODE="0666"
```

On certain Linux distributions, you may also have to manually set the permissions for ports to allow the app to communicate with the AudioMoth. If you experience connection issues, try the following command:
​
```
> sudo usermod -a -G dialout $(whoami)
```

## Building from source ##

USB HID Tool can be built on macOS using the Xcode Command Line Tools.

```
> clang -I./src/macOS/ -framework CoreFoundation -framework IOKit ./src/main.c ./src/macOS/hid.c -o usbhidtool
```

USB HID Tool can be built on Windows using the Microsoft Visual C++ Build Tools. Note that to build the correct version you should run the command in the correct environment. Use the 'x64 Native Tools Command Prompt' to build the 64-bit binary on a 64-bit machine, and the 'x64_x86 Cross Tools Command Prompt' to build the 32-bit binary on a 64-bit machine.

```
cl /I.\src\windows\ ./src/main.c .\src\windows\hid.c /link /out:usbhidtool.exe SetupAPI.lib 
```

USB HID Tool can be built on Linux using `gcc`. If not already present, the `libusb` development library must be installed.

```
> sudo apt-get install libusb-1.0.0-dev
```

Then the source can be compiled.

```
gcc -Wall -std=c99 -I/usr/include/libusb-1.0 -I./src/linux/ -o usbhidtool ./src/main.c ./src/linux/hid.c -lusb-1.0 -lrt -lpthread
```

On macOS and Linux you can copy the resulting executable to `/usr/local/bin/` so it is immediately accessible from the terminal. On Windows copy the executable to a permanent location and add this location to the `PATH` variable.

## Pre-built binaries ##

Pre-built binaries are also available in the repository.
