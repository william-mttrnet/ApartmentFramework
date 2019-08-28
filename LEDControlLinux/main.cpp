
#include <iostream>
#include <wiringPi.h>

// Our Own Modules
#include "apa102.h"
#include "sk6812rgbw.hpp"
#include "udp_frame.h"
#include "udp_low.hpp"

#define NUM_LEDS 500

// LED strip object
Apa102Pi strip_one; 

Sk6812RgbwPi strip_two; 

// Socket object recieving data
UDPFrame serv_socket; 
uint8_t led_array[NUM_LEDS * 16 + 200];

int main(void){
    strip_one.begin(led_array, NUM_LEDS, 255, 0);
    //strip_two.begin(led_array, NUM_LEDS, 255, 0);
    serv_socket.begin(5050);
    
    for(;;){
        // Waiting for data
        serv_socket.receive();
        
        // Setup LEDs and push!
        for(uint16_t i = 0; i < NUM_LEDS; i++){
            strip_one.set(serv_socket.in_array[i * 3 + 4], serv_socket.in_array[i * 3 + 5], serv_socket.in_array[i * 3 + 6], i);
        }        
        strip_one.update();
    }
}

