#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>

// tcp wrapper to make things more modular on the esp32
#include "tcpframe.h"

Serial debugger(USBTX, USBRX);

Thread tcp_frame_thread_handler; 
TCPFrame tcp_eth; 

void tcp_frame_thread_func(){
  tcp_eth.spin();
}

int main() {

  tcp_eth.begin("192.168.2.7", 69);
  
  for(;;){
    Thread::wait(1);
  }
}