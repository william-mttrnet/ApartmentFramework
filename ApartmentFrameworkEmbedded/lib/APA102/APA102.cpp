#include "WS2812B.h"

void WS2812B::begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver){
    this->SPIDriver = SPIDriver;
    this->num_leds = num_leds;
    this->bytearray = bytearray;

    this->SPIDriver->format(8, 3);
    // needs to as close to 2.4mhz as possible 
    // due to strict timing requirements of WS2812Bs
    this->SPIDriver->frequency(2500000);

    for(int i = 0; i < 4; i++){
        this->bytearray[i] = 0;
    }
}

void WS2812B::Set(uint8_t r, uint8_t g, uint8_t b, uint16_t pos){
    // sets up brightness!
    uint8_t red = ((r * this->brightness) >> 8); 
    uint8_t green = ((g * this->brightness) >> 8);
    uint8_t blue = ((b * this->brightness) >> 8);
   
    uint32_t led_pos = pos * 4 + 4;
     // set blue
    this->bytearray[led_pos + 1] = blue; 
    // set green
    this->bytearray[led_pos + 2] = green; 
    // set red
    this->bytearray[led_pos + 3] = red;  
}

void WS2812B::Update(void){
    // TODO
}

void WS2812B::SetBrightness(uint8_t brightness){
    this->brightness = brightness;
}