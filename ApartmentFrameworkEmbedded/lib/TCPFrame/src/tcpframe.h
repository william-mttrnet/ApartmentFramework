#ifndef _TCP_FRAME_H
#define _TCP_FRAME_H

#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>
#include "WS2812B_Animation.h"
#include <vector>

#define PACKET_SIZE 4500

class TCPFrame{
    public:
        // initializes the TCP interface. 
        void Begin(uint16_t port);
        
        // constantly checking for new data, and pinging the TCP server
        // to maintain a connection. 
        void Spin(void);

        bool new_led_frame(void);
        void SetStaticNetwork(const char *ip, const char *netmask, const char *gateway);

    private:

        void check_led();
        
        // packet contains led data, sending data to led thread
        void SetStrip(uint8_t strip);

        // ethernet interface
        EthernetInterface eth; 
        // socket interface B
        TCPSocket *socket;
        // server interface 
        TCPSocket server; 
        // ip address
        SocketAddress addr; 

        // is there a new led frame?
        int8_t latest_strip_frame = -1;
        
        // array to place all of our packet data
        uint8_t packet_arr[PACKET_SIZE] = {0};
        uint8_t msg_arr[4] = {0};
        uint16_t packet_size = 0; 
        uint16_t message_size = 0;
};

#endif