gcc -Wall -std=c99 -I/usr/include/libusb-1.0 -I.. -o ../../bin/linux/usbhidtool ../main.c hid.c -lusb-1.0 -lrt -lpthread
