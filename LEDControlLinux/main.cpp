
#include <iostream>
#include <wiringPi.h>

// Our Own Modules
#include "apa102.h"
#include "sk6812rgbw.hpp"
#include "udp_frame.h"
#include "udp_low.hpp"

#define NUM_LEDS 650

// LED strip object
Apa102Pi strip_one; 

Sk6812RgbwPi strip_two; 

// Socket object recieving data
UDPFrame serv_socket; 
uint8_t led_array[NUM_LEDS * 16 + 200];

int main(void){
    strip_one.begin(led_array, NUM_LEDS, 255, 0);
<<<<<<< HEAD
    //strip_two.begin(led_array, NUM_LEDS, 255, 0);
=======
<<<<<<< HEAD
=======
    //strip_two.begin(led_array, NUM_LEDS, 255, 0);
>>>>>>> 730a18e7559b4fcb19dab86876701c9ba7c4dab2
>>>>>>> c0c95f9b30d33f54f5404420a4cc24c71b12a5b3
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

