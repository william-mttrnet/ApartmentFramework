#include "sk6812.hpp"
#include <wiringPiSPI.h>
#include <stdint.h>

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <linux/spi/spidev.h>

static const char       *spiDev0  = "/dev/spidev0.0" ;
static const char       *spiDev1  = "/dev/spidev0.1" ;
static const uint8_t     spiBPW   = 8 ;
static const uint16_t    spiDelay = 0 ;

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

void Sk6812Pi::begin(uint8_t *led_array, uint32_t num_leds, uint8_t brightness, int spi_channel){
    // Adding pointer references and other important LED information. 
    this->led_array = led_array; 
    this->num_leds = num_leds; 
    this->brightness = brightness;
    this->led_array_size = this->num_leds * 12 + 200; 
    
    // SPI INIT BEGIN // 
    this->channel = spi_channel;
    
    int mode = 0; 
    int speed = 2400000;
    // Open up the spi driver!
    this->spi_id = open (channel == 0 ? spiDev0 : spiDev1, O_RDWR);
    
    // SPI Mode Change command 
    ioctl(this->spi_id, SPI_IOC_WR_MODE, &mode);
    
    // SPI Bits per Word change command
    ioctl (this->spi_id, SPI_IOC_WR_BITS_PER_WORD, &spiBPW);
    
    // SPI max frequency
    ioctl (this->spi_id, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    
    // SPI INIT END   // 
    
    for(uint32_t i = 0; i < this->num_leds; i++){
        this->set(0, 0, 0, i);
    }

    // Setting up end sequence
    for(uint8_t i = 0; i < 200; i++)
        this->led_array[this->led_array_size - (i + 1)] = 255;
    this->update();
}

void Sk6812Pi::set(uint8_t r, uint8_t g, uint8_t b, uint32_t led){
    // sets up brightness!
    uint8_t red = ((r * this->brightness) >> 8); 
    uint8_t green = ((g * this->brightness) >> 8);
    uint8_t blue = ((b * this->brightness) >> 8);

    for(int i = 0; i < 4; i++){
        // green is first color
        this->led_array[12 * led + i] = write_led_bits(green, i); 
        // red is 2nd color in this array 
        this->led_array[12 * led + 4+ i] = write_led_bits(red, i);
        // blue is third color
        this->led_array[12 * led + 8 + i] = write_led_bits(blue, i);
    }
}

void  Sk6812Pi::update(void){
    struct spi_ioc_transfer spi; 
    
    // Setting up the spi configuration message
    spi.tx_buf = (unsigned long)this->led_array;
    spi.rx_buf = NULL; 
    spi.len = this->led_array_size; 
    spi.delay_usecs = 0; 
    spi.speed_hz = 10000000; 
    spi.bits_per_word = spiBPW; 
    
    // Sending out the data
    ioctl(this->spi_id, SPI_IOC_MESSAGE(1), &spi);
}
