#ifndef _APA102_H
#define _APA102_H

// Raspberry Pi Hardware Dependencies
#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>

typedef struct{
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
}rgb_t;

class Apa102Pi{
    public: 
        // Setup function
        void begin(uint8_t *led_array, uint32_t num_leds, uint8_t brightness, int spi_channel);
        
        // Sets the LED to a specific color
        void set(uint8_t r, uint8_t g, uint8_t b, uint32_t led);
        
        // LEDS LEd to a specific rgb_t color value 
        void set(rgb_t col, uint32_t led);
        
        // Sends over new LED data over SPI
        void update(void);
        
        // Higher Level led abstraction stuff
        uint32_t num_leds; 
    private: 
        // LED array stuff
        uint8_t *led_array;
        uint32_t led_array_size;
        uint8_t brightness = 255; 
        
        int spi_id; 
        int channel = 0; 
};

#endif 
