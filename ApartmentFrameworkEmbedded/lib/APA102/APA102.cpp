#include "APA102.h"

void APA102::begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver){
    this->SPIDriver = SPIDriver;
    this->num_leds = num_leds;
    this->bytearray = bytearray;

    this->SPIDriver->format(8, 0);
    // needs to as close to 25mhz as possible 
    // due to strict timing requirements of APA102s
    this->SPIDriver->frequency(1400000);

    for(int i = 0; i < 4; i++){
        this->bytearray[i] = 0;
    }
}

void APA102::Set(uint8_t r, uint8_t g, uint8_t b, uint16_t pos){
    // sets up brightness!
    uint8_t red = ((r * this->brightness) >> 8); 
    uint8_t green = ((g * this->brightness) >> 8);
    uint8_t blue = ((b * this->brightness) >> 8);
   
    uint32_t led_pos = pos * 4 + 4;
    this->bytearray[led_pos] = 255;
     
     // set blue
    this->bytearray[led_pos + 1] = blue; 
    // set green
    this->bytearray[led_pos + 2] = green; 
    // set red
    this->bytearray[led_pos + 3] = red;  
}

void APA102::Update(void){
    this->SPIDriver->transfer(this->bytearray, this->num_leds * 4 + 8, this->bytearray, 0, NULL);
}

void APA102::SetBrightness(uint8_t brightness){
    this->brightness = brightness;
}