#include "SK6812.h"

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


void SK6812::begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver){
    this->SPIDriver = SPIDriver;
    this->num_leds = num_leds;
    this->bytearray = bytearray;
    
    // set default brightness
    this->brightness = 255;

    // setup SPI configuration stuff!
    this->SPIDriver->format(8, 0);
    // needs to as close to 2.4mhz as possible 
    // due to strict timing requirements of SK6812s
    this->SPIDriver->frequency(1200000);

}

void SK6812::Set(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint16_t pos){
    // sets up brightness!
    uint8_t red = ((r * this->brightness) >> 8); 
    uint8_t green = ((g * this->brightness) >> 8);
    uint8_t blue = ((b * this->brightness) >> 8);
    uint8_t white = ((white * this->brightness) >> 8);

    uint32_t led_pos = pos * 4;
    
    for(int i = 0; i < 4; i++){
        // green is first color
        this->bytearray[led_pos + i] = write_led_bits(green, i); 
        // red is 2nd color in strip array 
        this->bytearray[led_pos + 4 + i] = write_led_bits(red, i);
        // blue is third color
        this->bytearray[led_pos + 8 + i] = write_led_bits(blue, i);
        // white if the fourth color
        this->bytearray[led_pos + 12 + i] = write_led_bits(white, i);
    }
}

void SK6812::Update(void){
    this->SPIDriver->transfer(this->bytearray, this->num_leds * 4 + 100, this->bytearray, 0, NULL);
}

void SK6812::SetBrightness(uint8_t brightness){
    this->brightness = brightness;
}

