#include <mbed.h>
#include <rtos.h>
#include "led_strips.h"

#define STRIP_ONE_LEDS 334
#define STRIP_TWO_LEDS 334
#define STRIP_THREE_LEDS 334

Thread strip_one_thread;
SPI strip_one_spi(D14, D12, D13);
uint8_t strip_one_arr[STRIP_ONE_LEDS * 12];
WS2812B StripOne;
WS2812BAnimationHandler StripOneHandler;

Thread strip_two_thread;
SPI strip_two_spi(D14, D12, D13);
uint8_t strip_two_arr[STRIP_TWO_LEDS * 12];
WS2812B StripTwo;
WS2812BAnimationHandler StripTwoHandler;

Thread strip_three_thread;
SPI strip_three_spi(D14, D12, D13);
uint8_t strip_three_arr[STRIP_THREE_LEDS * 12];
WS2812B StripThree;
WS2812BAnimationHandler StripThreeHandler;

void StripOneFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripOne.begin(STRIP_ONE_LEDS, strip_one_arr, &strip_one_spi);
  StripOneHandler.AttachStrip(&StripOne);
  for(;;){
    StripOneHandler.Run();
  }
}

void StripTwoFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripTwo.begin(STRIP_TWO_LEDS, strip_two_arr, &strip_two_spi);
  StripTwoHandler.AttachStrip(&StripTwo);
  for(;;){
    StripTwoHandler.Run();
  }
}

void StripThreeFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripThree.begin(STRIP_THREE_LEDS, strip_three_arr, &strip_three_spi);
  StripThreeHandler.AttachStrip(&StripThree);
  for(;;){
    StripThreeHandler.Run();
  }
}

void SetupStrips(void){
    // kick off our LED control threads!
    strip_one_thread.start(StripOneFunc);
    strip_two_thread.start(StripTwoFunc);
    strip_three_thread.start(StripThreeFunc);
}

// so we can send a pointer reference of the animation handler to who ever needs it
WS2812BAnimationHandler* GetAnimationHandler(uint8_t strip_handle){
    switch (strip_handle)
        {
        case(1):
            return &StripOneHandler;
            break;
        
        case(2):
            return &StripTwoHandler;
            break;

        default:
            return &StripThreeHandler;
            break;
        }
}