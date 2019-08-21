#include "tcpframe.h"

void TCPFrame::Begin(uint16_t port){
    
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

    printf("Setting up TCP server!...\n");

    uint8_t counter = 0;

    if(this->server.open(&this->eth) < 0)
        printf("TCP Server could not open with the ethernet interface :(\n");
    else
        counter++;
    
    if(this->server.bind(eth.get_ip_address(), port))
        printf("TCP Server could not start broadcasting :(\n");
    else
        counter++;
    
    if(this->server.listen(10) < 0)
        printf("server had issues setting up a listener :(\n");
    else
        counter++;
    
    if(counter == 3)
        printf("TCP Setup properly!\n");

    this->server.set_blocking(true);
    this->server.set_timeout(-1);

    // accept a socket, set method calls as blocking
    // and timeout to zero
    this->socket = this->server.accept();
    this->socket->set_blocking(true);
    this->socket->set_timeout(-1);
}

void TCPFrame::SetStaticNetwork(const char *ip, const char *netmask, const char *gateway){
    // setting ethernet manually
    this->eth.set_network(ip, netmask, gateway);
}

void TCPFrame::Spin(void){
    // accepting a connection
    // if there is no new connection, then 
    // this doesn't do anything, other than return a number that doesn't
    // matter!

    // get the latest packet!
    this->packet_size = this->socket->recv(this->packet_arr, sizeof(this->packet_arr));
    
    // if there is 
    if(this->packet_size >= 6){
        // Message ID is contained within the first 4 bytes
        for(int i = 0; i < 4; i++){
            this->msg_arr[i] = this->packet_arr[i];
        }
        
        this->check_led();
    }   
}


void TCPFrame::check_led(){
    uint8_t val = 0; 
    for(int i = 0; i < 3; i++){
        if(this->msg_arr[i] == 16)
            val++;
    }

    // if 15 bytes have dec values of 16, it's an LED message!
    // and we can choose which strip to modify here
    if(val == 3)
        // if the stars align, 
        // then we set this int8 value to let us know which led strip we are using
        this->latest_strip_frame = this->msg_arr[3];
}