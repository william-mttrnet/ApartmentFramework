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

void TCPFrame::Spin(void){
    // accepting a connection
    // if there is no new connection, then 
    // this doesn't do anything, other than return a number that doesn't
    // matter
    char arr[140];
    memset(arr, 0, sizeof(arr));
    this->packet_size = this->socket->recv(arr, sizeof(arr));
    if(this->packet_size >1){
        printf(arr);
        printf("\n");
    }

    this->socket->send(arr, this->packet_size);

    /*
    if(this->packet_size >= 18){
        // Message ID is contained within the first 16 bytes
        for(int i = 0; i < 16; i++){
            this->msg_arr[i] = this->packet_arr[i];
        }

        uint8_t val = 0; 
        for(int i = 0; i < 15; i++){
            if(this->msg_arr[i] == 16)
                val++;
        }

        // if 15 bytes have dec values of 16, it's an LED message!
        // and we can choose which strip to modify here
        if(val == 15)
            this->SetStrip(msg_arr[15]);
    }
    */
    wait_ms(15);    
}

void TCPFrame::AttachAnimationHandler(WS2812BAnimationHandler *handler){
    this->strip_handler_list.push_back(handler);
}

void TCPFrame::RemoveAnimationHandler(uint8_t handler_num){
    this->strip_handler_list.erase(this->strip_handler_list.begin() + handler_num);
}

void TCPFrame::SetStrip(uint8_t strip){
    this->strip_handler_list[strip]->NewFrame(this->packet_arr, 18, sizeof(this->packet_arr));
}