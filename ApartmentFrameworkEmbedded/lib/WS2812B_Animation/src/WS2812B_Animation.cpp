#include "WS2812B_Animation.h"

#define FRAME_UPDATE 0 
#define INTERNAL_ANIMATION 1
#define DISABLED 2
#define FFT 3

void WS2812BAnimationHandler::AttachStrip(WS2812B *strip){
    this->strip = strip;
}

void WS2812BAnimationHandler::Run(void){
    switch(this->strip_mode){
        case(FRAME_UPDATE):
            if(this->new_frame)
                this->strip->Update();
            break;
        
        case(INTERNAL_ANIMATION):
            break;

        case(DISABLED):
            break;

        case(FFT):
            break;
    }
}

void WS2812BAnimationHandler::SetMode(uint8_t mode){
    this->strip_mode = mode;
}

void WS2812BAnimationHandler::NewFrame(uint8_t *frame, uint16_t start_val, uint16_t frame_size){
    uint16_t num_led = 0;

    if((frame_size/3) > this->strip->num_leds)
        num_led = this->strip->num_leds;
    else
        num_led = frame_size/3;
    
    for(uint16_t i = start_val; i < num_led; i++){
        this->strip->Set(frame[i * 3], frame[i * 3 + 1], frame[i * 3 + 2], i);
    }
    this->new_frame = true;
}   
