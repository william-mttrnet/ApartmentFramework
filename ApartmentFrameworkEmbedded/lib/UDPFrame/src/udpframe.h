#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>
#include "APA102.h"

#define PACKET_SIZE 8000

class UDPFrame{
    public: 
        // Call this before you enable the TCP interface. It will
        // statically set your IP address
        void SetStaticNetwork(const char *ip, const char *netmask, const char *gateway);
        
        // Throw this into a thread, and it will do it's own thing!
        void Run(uint16_t port);

        // Save strip references
        void AttachStrip(APA102 *ref, uint8_t pl);

    private: 
        // ethernet interface
        EthernetInterface eth; 
        // IP address
        SocketAddress recieve; 
        // Thread handler for udp stuff!
        Thread udp_thread;
        // Pointer reference to a socket.  
        UDPSocket *socket;

        // array to place all of our packet data
        uint8_t packet_arr[PACKET_SIZE] = {0};
        uint8_t msg_arr[4] = {0};
        uint16_t packet_size = 0; 
        uint16_t message_size = 0;

        APA102 *strip_point[6];

        // Internal Function that will check if LEDs have been changed.
        void CheckLEDs(void);

}; 