#ifndef _SK6812_H
#define _SK6812_H

#include "mbed.h"

class SK6812{
    public: 
        // setup leds 
        void begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver);

        // set a specific LED to a specific color
        void Set(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint16_t pos);

        // set a brightness
        void SetBrightness(uint8_t brightness);
        
        // push up the changes to the SPI device
        void Update(void);
        
        uint16_t num_leds;
        
    private:
        SPI *SPIDriver;
        uint8_t *bytearray;
        uint8_t brightness; 

};
#endif