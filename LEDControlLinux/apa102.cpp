#include "apa102.h"
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

static uint32_t    spiSpeeds [2] ;
static int         spiFds [2] ;

void Apa102Pi::begin(uint8_t *led_array, uint32_t num_leds, uint8_t brightness, int spi_channel){
    // Adding pointer references and other important LED information. 
    this->led_array = led_array; 
    this->num_leds = num_leds; 
    this->brightness = brightness;
    this->led_array_size = this->num_leds * 4 + 8; 
    
    // SPI INIT BEGIN // 
    this->channel = spi_channel;
    int mode = 0; 
    int speed = 5000000;
    // Open up the spi driver!
    this->spi_id = open (channel == 0 ? spiDev0 : spiDev1, O_RDWR);
    
    // SPI Mode Change command 
    ioctl(this->spi_id, SPI_IOC_WR_MODE, &mode);
    
    // SPI Bits per Word change command
    ioctl (this->spi_id, SPI_IOC_WR_BITS_PER_WORD, &spiBPW);
    
    // SPI max frequency
    ioctl (this->spi_id, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    
    // SPI INIT END   // 
    
    // Setting up the interfacing for the LEDs. 
    for(int i = 0; i < 4; i++){
        // Begining Sequence
        this->led_array[i] = 0; 
    }
    
    for(uint32_t i = 0; i < this->num_leds; i++){
        this->set(0, 0, 0, i);
    }
    this->update();
}

void Apa102Pi::set(uint8_t r, uint8_t g, uint8_t b, uint32_t led){
    uint32_t led_pos = led * 4 + 4; 
    
    // Setting the brightness
    this->led_array[led_pos] = 255;
    
    // Setting the right datat in the LED array
    this->led_array[led_pos + 1] = b; 
    this->led_array[led_pos + 2] = g; 
    this->led_array[led_pos + 3] = r; 
}

void  Apa102Pi::update(void){
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
