#ifndef _UDP_FRAME_H
#define _UDP_FRAME_H

// General C++ and Raspberry Pi stuff!
#include "wiringPi.h"
#include <iostream>

// Socket stuff
#include <sys/socket.h>

class UDPFrame{
    public: 
        void begin(uint16_t port);

    private:
        int sock_fd; 
};

#endif
