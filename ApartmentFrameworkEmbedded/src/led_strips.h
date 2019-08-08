#include "WS2812B_Animation.h"
#include "APA102.h"
// setup the strip from the main file
void SetupStrips(void);

// get a pointer to the animation handler
WS2812BAnimationHandler* GetAnimationHandler(uint8_t strip_handle);