#ifndef _TCP_FRAME_H
#define _TCP_FRAME_H

#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>

class TCPFrame{
    public:
        void begin();
    private:
        EthernetInterface eth; 
};

#endif