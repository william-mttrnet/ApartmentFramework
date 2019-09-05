#include "udp_frame.h"

void UDPFrame::begin(uint16_t port){
    udp_server_socket_open(port);
}

void UDPFrame::receive(void){
    this->latest_packet_in_size = udp_server_receive_blocking(this->in_array);
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
