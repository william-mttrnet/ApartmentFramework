#ifndef _RGB_STRIP_COMMON_HPP
#define _RGB_STRIP_COMMON_HPP

// RGB shared struct
typedef struct{
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
}rgb_t;

// RGBW shared struct
typedef struct{
    uint8_t r; 
    uint8_t g; 
    uint8_t b; 
    uint8_t w;
}rgbw_t;

#endif 