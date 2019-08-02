#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>

// tcp wrapper to make things more modular on the esp32
#include "tcpframe.h"

// LED Strip Inferfacing module
#include "WS2812B.h"
#include "APA102.h"

#define STRIP_ONE_LEDS 334
#define STRIP_TWO_LEDS 334
#define STRIP_THREE_LEDS 334

Serial debugger(USBTX, USBRX);

// All the stuff handling ethernet/tcp communication
Thread tcp_frame_thread_handler; 
TCPFrame tcp_eth; 

Thread strip_one_thread;
SPI strip_one_spi(D14, D12, D13);
uint8_t strip_one_arr[STRIP_ONE_LEDS * 12];
WS2812B StripOne;

Thread strip_two_thread;
SPI strip_two_spi(D14, D12, D13);
uint8_t strip_two_arr[STRIP_TWO_LEDS * 12];
WS2812B StripTwo;

Thread strip_three_thread;
SPI strip_three_spi(D14, D12, D13);
uint8_t strip_three_arr[STRIP_THREE_LEDS * 12];
WS2812B StripThree;

void StripOneFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripOne.begin(STRIP_ONE_LEDS, strip_one_arr, &strip_one_spi);
  for(;;){

  }
}

void StripTwoFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripTwo.begin(STRIP_TWO_LEDS, strip_two_arr, &strip_two_spi);
  for(;;){

  }
}

void StripThreeFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripThree.begin(STRIP_THREE_LEDS, strip_three_arr, &strip_three_spi);
  for(;;){

  }
}

int main() {
  // kick off our LED control threads!
  strip_one_thread.start(StripOneFunc);
  strip_two_thread.start(StripTwoFunc);
  strip_three_thread.start(StripThreeFunc);

  //  kick off our tcp thread!
  tcp_eth.Begin("192.168.2.7", 69);
  
  for(;;){
    tcp_eth.Spin();
  }
}