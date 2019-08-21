#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>
#include "led_strips.h"

// tcp wrapper to make things more modular on the esp32
#include "tcpframe.h"

// LED Strip Inferfacing module
#include "WS2812B.h"
#include "APA102.h"

#include "ApartmentProtobuff/status.pb.h"

Serial debugger(USBTX, USBRX);

// All the stuff handling ethernet/tcp communication
Thread tcp_frame_thread_handler; 
TCPFrame tcp_eth; 

int main() {
  // letting me know that the mbed at least booted up!
  debugger.printf("Starting up subsystems!\n");

  // kickoff all the strip stuff!
  SetupStrips();
  //  kick off our tcp thread!
  // setting ethernet manually
  tcp_eth.SetStaticNetwork("192.168.7.2", "255.255.252.0", "192.168.7.1");
  tcp_eth.Begin(5005);
  
  for(;;){
    tcp_eth.Spin();
    wait(1);
  }
  return 0;
}
