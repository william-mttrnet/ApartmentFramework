#include <iostream>
#include <wiringPi.h>

// Our Own Modules
#include "apa102.h"
#include "udp_frame.h"

#define NUM_LEDS 500

// LED strip object
Apa102Pi strip_one; 

// Socket object recieving data
UDPFrame serv_socket; 
uint8_t led_array[NUM_LEDS * 4 + 8];

int main(void){
    strip_one.begin(led_array, NUM_LEDS, 255, 0);
    
    for(;;){
        for(int i = 0; i < NUM_LEDS; i++){
            strip_one.set(10, 10, 10, i);
            strip_one.update();
            delay(15);
        }        
        
        for(int i = 0; i < NUM_LEDS; i++){
            strip_one.set(0, 0, 0, i);
            strip_one.update();
            delay(15);
        }        
    }
}
