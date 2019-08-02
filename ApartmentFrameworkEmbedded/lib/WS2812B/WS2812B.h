#ifndef _WS2812B_H
#define _WS2812B_H

#include "mbed.h"

class WS2812B{
    public: 
        // setup leds 
        void begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver);

        // set a specific LED to a specific color
        void Set(uint8_t r, uint8_t g, uint8_t b, uint16_t pos);

        // set a brightness
        void SetBrightness(uint8_t brightness);
        
        // push up the changes to the SPI device
        void Update(void);
    private:
        SPI *SPIDriver;
        uint16_t num_leds;
        uint8_t *bytearray;
        uint8_t brightness; 

};

#endif