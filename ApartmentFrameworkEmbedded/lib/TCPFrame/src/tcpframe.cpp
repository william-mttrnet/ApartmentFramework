#include "tcpframe.h"

void TCPFrame::Begin(const char *host, uint16_t port){
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

void TCPFrame::Spin(void){
    
    if(this->packet_size = socket.recv(&this->packet_arr, sizeof(packet_arr)) >= 18){
        
        // Message ID is contained within the first 16 bytes
        for(int i = 0; i < 16; i++){
            this->msg_arr[i] = this->packet_arr[i];
        }

        // message size is contained within the next 2 bytes
        this->message_size = (this->packet_arr[16] << 8) | (this->packet_arr[17]);
    }

    uint8_t val = 0; 
    for(int i = 0; i < 16; i++){
        if(this->msg_arr[i] == 16)
            val++;
    }

    // if all 16 bytes have dec values of 16, it's an LED message!
    if(val == 16)
        this->SendLED();

    // gotta give the rtos time 
    // to other stuff
    // this should give us plenty of FPS with LEDs
    // and the ability to check for other messages as well

    wait_ms(15);    
}

void TCPFrame::SendLED(void){

}
