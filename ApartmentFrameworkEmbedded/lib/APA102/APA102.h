#ifndef _APA102_H
#define _APA102_H

#include <mbed.h>
#include <rtos.h>

class APA102{
    public: 
        // setup leds 
        void begin(uint16_t num_leds, uint8_t *bytearray, SPI *SPIDriver);

        // set a specific LED to a specific color
        void Set(uint8_t r, uint8_t g, uint8_t b, uint16_t pos);

        // set a brightness
        void SetBrightness(uint8_t brightness);
        
        // push up the changes to the SPI device
        void Update(void);

        // Set the entire strip to an rgb value
        void SetStrip(uint8_t r, uint8_t g, uint8_t b);
        
        // Waits for semaphore to signal an update sequence. 
        void WaitOnPacket(void);

        // Signals semaphore to unlock packet update 
        void SignalPacketReady(void);
    private:
        // Where to we update the LEDs?
        SPI *SPIDriver;
        // How many LEDs are there?
        uint16_t num_leds;
        // Byte array reference
        uint8_t *bytearray;
        // Default brightness
        uint8_t brightness = 255;

        // Signals that an update is ready
        EventFlags update_signal; 

};

#endif