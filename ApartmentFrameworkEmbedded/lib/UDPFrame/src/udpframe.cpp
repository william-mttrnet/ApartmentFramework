#include "udpframe.h"

void UDPFrame::SetStaticNetwork(const char *ip, const char *netmask, const char *gateway){
    // setting ethernet manually
    this->eth.set_network(ip, netmask, gateway);
}

void UDPFrame::Run(uint16_t port){
    // setting up the ethernet interface
    printf("Setting up ethernet jack...");
    
    this->eth.connect();
    printf("done!\n");

    // network stuff!
    const char *ip = this->eth.get_ip_address();
    const char *netmask = this->eth.get_netmask();
    const char *gateway = this->eth.get_gateway();

    // print out typical data to the terminal
    // hopefully will help with debugging 
    
    printf("IP Address:  %s\n", ip ? ip : "None");
    printf("Netmask: %s\n", netmask ? netmask : "None");
    printf("Gateway: %s\n", gateway ? gateway : "None");
    
    // Creating a socket attached to our ethernet port
    UDPSocket socket(&eth);
    
    // Connect that socket to a specific port.
    int bind = socket.bind(port);
    socket.set_blocking(true);
    socket.set_timeout(-1);

    printf("Socket has been created! waiting for data \n");
    
    for(;;){
        // waiting for a packet to come in
        this->packet_size = socket.recvfrom(&this->recieve, &this->packet_arr, sizeof(this->packet_arr));
        
        // check LED stuff, trigger something if needed
        this->CheckLEDs();

        // slow things down for the thread
        wait_ms(10);
    }
}

// Send over strip references
void UDPFrame::AttachStrip(APA102 *ref, uint8_t pl){
    this->strip_point[pl] = ref; 
}

void UDPFrame::CheckLEDs(void){
    // If the stars align, we will program a led strip
    if(this->packet_arr[0] == 16 && this->packet_arr[1] == 16 && this->packet_arr[2] == 16){
        
        // Just a print statement for debugging, must be removed later!
        printf("Strip %d with %d LEDs has been requested to update\n", this->packet_arr[3], ((this->packet_size - 4)/3));
        
        // Go through the entire array and set the rgb values
        // on a strip pointer. 
        for(uint16_t i = 0; i < (this->packet_size - 4)/3; i++){
            this->strip_point[this->packet_arr[3]]->Set(this->packet_arr[(i * 3) + 4], this->packet_arr[(i * 3) + 5], this->packet_arr[(i * 3) + 6], i);
        }
        // Releases semaphore 
        this->strip_point[this->packet_arr[3]]->SignalPacketReady();
        
    }
}