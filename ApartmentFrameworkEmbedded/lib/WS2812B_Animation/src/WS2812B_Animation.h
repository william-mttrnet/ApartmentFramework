#ifndef _WS2812B_ANIMATION_H
#define _WS2812B_ANIMATION_H

#include "WS2812B.h"

class WS2812BAnimationHandler{
    public: 
        void AttachStrip(WS2812B *strip);
        void Run(void);
        void SetMode(uint8_t mode);
        void NewFrame(uint8_t *frame, uint16_t start_val, uint16_t frame_size);
        
    private:
        WS2812B *strip;
        uint8_t strip_mode = 0; 
        bool new_frame; 
};

#endif