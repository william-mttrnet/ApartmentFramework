#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>
#include "led_strips.h"

// udp wrapper to make things more modular on the esp32
#include "udpframe.h"

// LED Strip Inferfacing module
#include "WS2812B.h"
#include "APA102.h"

Thread udp_thread; 
UDPFrame udp_eth;

Serial debugger(USBTX, USBRX);

void RunNetworking(void){
  // Running the UDP. 
  udp_eth.Run(5005);
}

void SetupNetworking(void){
  // Kick off our udp thread!
  // Setting ethernet manually.
  udp_eth.SetStaticNetwork("192.168.7.2", "255.255.252.0", "192.168.7.1");
  
  // Save pointer references for three apa102 strips!
  for(int i = 0; i < 3; i++){
    udp_eth.AttachStrip(get_strips(i), i);
  }

  // Start the networking thread, which will do all it's coolness
  udp_thread.start(RunNetworking);
}

int main() {
  // letting me know that the mbed at least booted up!
  debugger.printf("Starting up subsystems!\n");

  // Kickoff all the strip stuff!
  SetupStrips();

  // Setting up the Networking stuff. 
  SetupNetworking();
}