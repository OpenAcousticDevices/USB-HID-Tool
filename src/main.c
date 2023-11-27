
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "hidapi.h"

#define PACKETSIZE  64

uint8_t inputBuffer[PACKETSIZE];
uint8_t outputBuffer[PACKETSIZE];

struct hid_device_info *device_info;

/* Function to print buffer */

void printBuffer(uint8_t *buffer) {
    
    for (int i = 0; i < PACKETSIZE - 1; i += 1) {
        
        printf("%02x ", buffer[i]);
        
    }
    
    printf("%02x\n", buffer[PACKETSIZE - 1]);
    
}

/* Main function */

int main(int argc, char **argv) {

    /* Check at least 2 argument */
    
    if (argc < 3) {
        
        printf("ERROR: No VID or PID specified\n");
        
        return 0;
    
    }
    
    uint16_t vid = strtol(argv[1], NULL, 0);
    
    uint16_t pid = strtol(argv[2], NULL, 0);
    
    /* Connect to device */

    device_info = hid_enumerate(vid, pid);
    
    if (device_info != NULL) {
        
        hid_device *device = hid_open(device_info->vendor_id, device_info->product_id, device_info->serial_number);
        
        if (device != NULL) {
            
            int i = 3;
            
            while (i < argc) {
                
                int j = 0;
                
                memset(outputBuffer, 0, PACKETSIZE);
                
                while (j < PACKETSIZE && i < argc) {
                    
                    outputBuffer[j] = strtol(argv[i], NULL, 0);
                    
                    i += 1;
                    j += 1;
                    
                }
                
                hid_write(device, outputBuffer, PACKETSIZE);
                
                int length = hid_read_timeout(device, inputBuffer, PACKETSIZE, 100);
                
                if (length != PACKETSIZE) {
                    
                    printf("ERROR: Incorrect response from device\n");
                    
                    return 0;
                    
                }
                
            }
                    
            printBuffer(inputBuffer);
            
            hid_close(device);
            
        } else {
            
            printf("ERROR: Could not connect to device\n");
            
        }
            
    } else {
        
        printf("NULL\n");
        
    }

    return 0;

}
