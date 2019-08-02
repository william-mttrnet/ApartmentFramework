#ifndef _TCP_FRAME_H
#define _TCP_FRAME_H

#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>

#define IP_ADDR_TEST "192.168.7.2"
#define PACKET_SIZE 65000

class TCPFrame{
    public:
        // initializes the TCP interface. 
        void Begin(const char *host, uint16_t port);
        
        // constantly checking for new data, and pinging the TCP server
        // to maintain a connection. 
        void Spin(void);

        // packet contains led data, sending data to led thread
        void SendLED(void);

    private:
        // ethernet interface
        EthernetInterface eth; 
        // socket interface 
        TCPSocket socket; 
        
        // array to place all of our packet data
        uint8_t packet_arr[PACKET_SIZE] = {0};
        uint8_t msg_arr[16] = {0};
        uint16_t packet_size = 0; 
        uint16_t message_size = 0;
    
};

#endif