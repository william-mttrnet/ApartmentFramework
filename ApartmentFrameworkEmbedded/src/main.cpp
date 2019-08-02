#include <mbed.h>
#include <rtos.h>
#include <EthernetInterface.h>

// tcp wrapper to make things more modular on the esp32
#include "tcpframe.h"

// our serializeation stuff
#include "pb_common.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "ProtobufHeaders/status.pb.h"

Serial debugger(USBTX, USBRX);

TCPFrame tcp_eth; 

int main() {

  tcp_eth.begin();
    
  for(;;){
    Thread::wait(1);
  }
}