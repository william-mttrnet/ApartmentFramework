#ifndef _UDP_FRAME_H
#define _UDP_FRAME_H

// General C++ and Raspberry Pi stuff!
#include "wiringPi.h"
#include "udp_low.h"
#include <iostream>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PACKET_MAX_SIZE 32768
// Object wrapper for UDP c function. Only use a single instance of this at a time. 
class UDPFrame{
    public: 
        
        // Starting a server. 
        void begin(uint16_t port);
        
        // Blocking function that waits for data to be received. 
        void receive(void);
        
        // Send packet array to latest ip address and port. 
        void send(void);
        
        // Send to packet array to a desired ip address and port.
        void sendto(uint16_t port, const char *arr);
        
        // Check message ID to see if it's a new frame coming in. 
        bool NewMatrixFrame(void);
        bool NewMatrixText(void);
        
        // In and out arrays. 
        uint8_t in_array[PACKET_MAX_SIZE];
        uint16_t latest_packet_in_size = 0;
        
        uint16_t latest_packet_out_size = 0;
        uint8_t out_array[PACKET_MAX_SIZE]; 
        
        // First four bytes get unpacked into a "latest packet id" 
        uint32_t latest_packet_id; 
        
    private:
        // udp socket descriptor
        int sock_fd; 
};

#endif
