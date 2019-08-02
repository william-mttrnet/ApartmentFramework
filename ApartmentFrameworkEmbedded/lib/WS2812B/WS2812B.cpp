#include "WS2812B.h"

static uint8_t write_led_bits(uint8_t data, uint8_t pos){
    // out bit buffer
    uint8_t out_bits = 0; 
    
    // checking first bit in defined pos
    if(data & (1 << (2*(3-pos)))){
        out_bits = 0b1110; 
    }
    else{
        out_bits = 0b1000; 
    }

    // 2nd bit it in defined pos
    if(data & (2 << (2*(3-pos)))){
        out_bits += 0b11100000; 
    }
    else{
        out_bits += 0b10000000; 
    }
    return out_bits; 
}


void WS2812B::begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver){
    this->SPIDriver = SPIDriver;
    this->num_leds = num_leds;
    this->bytearray = bytearray;
    
    this->SPIDriver->format(8, 3);
    // needs to as close to 2.4mhz as possible 
    // due to strict timing requirements of WS2812Bs
    this->SPIDriver->frequency(2500000);

}

void WS2812B::Set(uint8_t r, uint8_t g, uint8_t b, uint16_t pos){
    // sets up brightness!
    uint8_t red = ((r * this->brightness) >> 8); 
    uint8_t green = ((g * this->brightness) >> 8);
    uint8_t blue = ((b * this->brightness) >> 8);

    for(int i = 0; i < 4; i++){
        // green is first color
        this->bytearray[12 * pos + i] = write_led_bits(green, i); 
        // red is 2nd color in strip array 
        this->bytearray[12 * pos + 4+ i] = write_led_bits(red, i);
        // blue is third color
        this->bytearray[12 * pos + 8 + i] = write_led_bits(blue, i);
    }
}

void WS2812B::Update(void){
    // TODO
}

void WS2812B::SetBrightness(uint8_t brightness){
    this->brightness = brightness;
}

