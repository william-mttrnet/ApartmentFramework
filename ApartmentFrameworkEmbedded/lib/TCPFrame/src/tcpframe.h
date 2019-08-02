#ifndef _TCP_FRAME_H
#define _TCP_FRAME_H

#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>

#define IP_ADDR_TEST "192.168.7.2"

class TCPFrame{
    public:
        // initializes the TCP interface. 
        void begin(const char *host, uint16_t port);
        
        // constantly checking for new data, and pinging the TCP server
        // to maintain a connection. 
        void spin(void);
    private:
        // ethernet interface
        EthernetInterface eth; 
        // socket interface 
        TCPSocket socket; 
        
        // array to place all of our packet data
        uint8_t packet_arr[65000] = {0};
        uint16_t packet_size = 0; 
};

#endif