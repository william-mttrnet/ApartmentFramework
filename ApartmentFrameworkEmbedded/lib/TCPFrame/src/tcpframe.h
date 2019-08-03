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

        // attach an animation handler pointer reference
        void AttachAnimationHandler(WS2812BAnimationHandler *handler);

        // remove an animation handler
        void RemoveAnimationHandler(uint8_t handler_num);

    private:
        // packet contains led data, sending data to led thread
        void SetStrip(uint8_t strip);

        // ethernet interface
        EthernetInterface eth; 
        // socket interface B
        TCPSocket socket;
        // server interface 
        TCPServer server; 
        // ip address
        SocketAddress addr; 
        
        // array to place all of our packet data
        uint8_t packet_arr[PACKET_SIZE] = {0};
        uint8_t msg_arr[16] = {0};
        uint16_t packet_size = 0; 
        uint16_t message_size = 0;

        std::vector<WS2812BAnimationHandler*> strip_handler_list;
};

#endif