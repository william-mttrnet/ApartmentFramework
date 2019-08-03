#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>
#include "led_strips.h"

// tcp wrapper to make things more modular on the esp32
#include "tcpframe.h"

// LED Strip Inferfacing module
#include "WS2812B.h"
#include "APA102.h"

#include "WS2812B_Animation.h"

#include "ApartmentProtobuff/status.pb.h"

Serial debugger(USBTX, USBRX);

// All the stuff handling ethernet/tcp communication
Thread tcp_frame_thread_handler; 
TCPFrame tcp_eth; 

int main() {
  // kickoff all the strip stuff!
  SetupStrips();
  //  kick off our tcp thread!
  tcp_eth.Begin(69);
  
  for(;;){
    tcp_eth.Spin();
  }
}