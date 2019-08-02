#include "tcpframe.h"

void TCPFrame::begin(const char *host, uint16_t port){
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
    printf("this->Socket %s\n", ip ? ip : "None");
    printf("Netmask: %s\n", netmask ? netmask : "None");
    printf("Gateway: %s\n", gateway ? gateway : "None");

    printf("Setting up TCP this->socket...");
    // open up the ethernet port to the TCP this->socket
    this->socket.open(&this->eth);

    // connect the this->socket obeject to an ip address at
    // a defined port
    if(this->socket.connect(host, port)){
        printf("done!\n");
    }

    // if it doesn't work, keep trying
    // I'm aware this can leed to a loop runtime error
    // but the entire thing relies on having an active 
    else{
        printf("connectio failed :( Retrying \n");
        while(!this->socket.connect(host, port)){
            
            printf("connectio failed :( Retrying\n");
            wait(1);
        }
        printf("done!\n");
    }
}

void TCPFrame::spin(void){
    
    socket.recv(&this->packet_arr, sizeof(packet_arr));
    // gotta give the rtos time 
    // to other stuff
    // this should give us plenty of FPS with LEDs
    // and the ability to check for other messages as well
    wait_ms(15);    
}

