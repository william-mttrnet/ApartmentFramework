#include "udp_frame.h"

void UDPFrame::begin(uint16_t port){
    udp_server_socket_open(port);
}

void UDPFrame::receive(void){
    this->latest_packet_in_size = udp_server_receive_blocking(this->in_array);
    
    this->latest_packet_id = (this->in_array[0] << 24) | (this->in_array[1] << 16) | (this->in_array[2] << 8) | this->in_array[3];
}

void UDPFrame::send(void){
    udp_server_send(this->latest_packet_out_size, this->out_array);
}

void UDPFrame::sendto(uint16_t port, const char *arr){
    
    // Build struct with send address and port
    struct sockaddr_in send_address;
    bzero(&send_address, sizeof(send_address));
    send_address.sin_addr.s_addr = inet_addr(arr);
    send_address.sin_port = htons(port);
    send_address.sin_family = AF_INET;
    
    // send out the data
    udp_server_sendto(this->latest_packet_out_size, this->out_array, &send_address);
}

bool UDPFrame::NewMatrixFrame(void){
    uint8_t m = 0; 
    for(uint8_t i = 0; i < 4; i++){
        if(this->in_array[i] == 15)
            m++;
    }
    if(m == 4){
        return true;
    }
    return false; 
}

bool UDPFrame::NewMatrixText(void){
    uint8_t m = 0;
    for(uint8_t i = 0; i < 3; i++){
        if(this->in_array[i] == 15)
            m++;
    }
    if(m == 4){
        return true;
    }
    return false; 
    
}
