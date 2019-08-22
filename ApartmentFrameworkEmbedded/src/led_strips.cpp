#include <mbed.h>
#include <rtos.h>
#include "led_strips.h"

// LED strip stuff!
#include "APA102.h"
#include "SK6812.h"

// SPI Format: (SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS)

// The first 3 strips are currently APA102s! They are 
// Faster, take up 1/4th the space as SK6812s, and can be updated
// Orders of magnitude faster

#define STRIP_ONE_LEDS 334
#define STRIP_TWO_LEDS 334
#define STRIP_THREE_LEDS 334

Thread strip_one_thread;
SPI strip_one_spi(PB_5, PB_4, PB_3);
uint8_t strip_one_arr[STRIP_ONE_LEDS * 4 + 8];
APA102 StripOne;

Thread strip_two_thread;
SPI strip_two_spi(PB_15, PC_2, PB_13);
uint8_t strip_two_arr[STRIP_TWO_LEDS * 4 + 8];
APA102 StripTwo;

Thread strip_three_thread;
SPI strip_three_spi(PC_12, PC_11, PC_10);
uint8_t strip_three_arr[STRIP_THREE_LEDS * 4 + 8];
APA102 StripThree;

// The next three strips are SK6812s
// These don't update anywhere nearly as fast
// But they are rgbw, meaning they get white!
// And because of this, they get wayy brighter!
#define STRIP_FOUR_LEDS 12
#define STRIP_FIVE_LEDS 334
#define STRIP_SIX_LEDS 334

Thread strip_four_thread;
SPI strip_four_spi(PE_6, PE_5, PE_2);
uint8_t strip_four_arr[STRIP_FOUR_LEDS * 16 + 100];
SK6812 StripFour;

Thread strip_five_thread;
SPI strip_five_spi(PF_9, PF_8, PF_7);
uint8_t strip_five_arr[STRIP_FIVE_LEDS * 16 + 100];
SK6812 StripFive;

Thread strip_six_thread;
SPI strip_six_spi();
uint8_t strip_six_arr[STRIP_SIX_LEDS * 16 + 100];
SK6812 StripSix;

APA102* get_strips(uint8_t r){
  switch(r){
    case(0):
      return &StripOne;
    case(1):
      return &StripTwo;
    case(2):
      return &StripThree;
  }
}

void StripOneFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripOne.begin(STRIP_ONE_LEDS, strip_one_arr, &strip_one_spi);

  for(uint16_t i = 0; i < STRIP_ONE_LEDS; i++)
    StripOne.Set(0, 0, 0, i);
  StripOne.Update();
  printf("Strip One has been setup successfully\n");

  // Now we just wait on for new data 
  // from the ethernet interface and go nuts!
  for(;;){
    StripOne.WaitOnPacket();
    printf("Strip one has recieved a new update! \n");  
    StripOne.Update();
  }
}

void StripTwoFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver

  StripTwo.begin(STRIP_TWO_LEDS, strip_two_arr, &strip_two_spi);

  for(uint16_t i = 0; i < STRIP_TWO_LEDS; i++)
    StripTwo.Set(0, 0, 0, i);
  StripTwo.Update();
  printf("Strip Two has been setup successfully\n");

  // Now we just wait on for new data 
  // from the ethernet interface and go nuts!
  for(;;){
    StripTwo.WaitOnPacket();
    printf("Strip two has recieved a new update! \n");
    StripTwo.Update();
  }  
}

void StripThreeFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripThree.begin(STRIP_THREE_LEDS, strip_three_arr, &strip_three_spi);

  for(uint16_t i = 0; i < STRIP_THREE_LEDS; i++)
    StripThree.Set(0, 0, 0, i);
  StripThree.Update();
  printf("Strip Three has been setup successfully\n");
  
  // Now we just wait on for new data 
  // from the ethernet interface and go nuts!
  for(;;){
    StripThree.WaitOnPacket();
    printf("Strip three has recieved a new update! \n");
    StripThree.Update();
  }  
}

void StripFourFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripFour.begin(STRIP_FOUR_LEDS, strip_four_arr, &strip_four_spi);

  for(uint16_t i = 0; i < STRIP_FOUR_LEDS; i++)
    StripFour.Set(0, 0, 0, 0, i);
  StripFour.Update();

  for(;;){
    for(uint16_t i = 0; i < STRIP_FOUR_LEDS; i++)
      StripFour.Set(0, 0, 0, 0, i);
    StripFour.Update();
    
    wait(1);
    
    for(uint16_t i = 0; i < STRIP_FOUR_LEDS; i++)
      StripFour.Set(100, 100, 100, 100, i);
    StripFour.Update();
    
    wait(1);
  }
  printf("Strip Four has been setup successfully\n");
}

void StripFiveFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  StripFive.begin(STRIP_FIVE_LEDS, strip_five_arr, &strip_five_spi);
  
  for(uint16_t i = 0; i < STRIP_FIVE_LEDS; i++)
    StripFive.Set(0, 0, 0, 0, i);
  StripFive.Update();
  printf("Strip Five has been setup successfully\n");
}

void StripSixFunc(){
  // setting up all of the LED strips
  // then combining them all with the propper arrays
  // and spi driver
  // StripSix.begin(STRIP_SIX_LEDS, strip_six_arr, &strip_six_spi);
  
  for(uint16_t i = 0; i < STRIP_SIX_LEDS; i++)
    StripSix.Set(0, 0, 0, 0, i);
  StripSix.Update();
  printf("Strip Six has been setup successfully\n");
}

void SetupStrips(void){
    // kick off our LED control threads!
    strip_one_thread.start(StripOneFunc);
    wait(1);
    strip_two_thread.start(StripTwoFunc);
    wait(1);
    strip_three_thread.start(StripThreeFunc);
    wait(1);
    //strip_four_thread.start(StripFourFunc);
    //wait(1);
    //strip_five_thread.start(StripFiveFunc);
    
    // currently I don't have access to these SPI pins, so we 
    // won't bother with this!
    //strip_six_thread.start(StripSixFunc);
}