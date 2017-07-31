gcc -Wall -std=c99 -I/usr/include/libusb-1.0 -I.. -o usbhidtool ../main.c hid.c -lusb-1.0 -lrt -lpthread

cp usbhidtool ../../bin/linux/usbhidtool

rm -f usbhidtool
