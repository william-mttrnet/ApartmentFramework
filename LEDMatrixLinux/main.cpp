#include <iostream>
#include <wiringPi.h>

#include "udp_frame.h"
#include "udp_low.h"
#include "rpi-rgb-led-matrix/include/led-matrix.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// Socket object recieving data
UDPFrame serv_socket; 

int main(int argc, char *argv[]){
    //strip_two.begin(led_array, NUM_LEDS, 255, 0);
    // serv_socket.begin(5050);
    
    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;
    if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
       
    }
  
    rgb_matrix::RGBMatrix *matrix =  rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                          runtime_opt);
    if (matrix == NULL)
        return 1;

    matrix->SetBrightness(100);
    matrix->Clear();
    
    rgb_matrix::FrameCanvas *offscreen = matrix->CreateFrameCanvas();
    offscreen->Clear();
    
    offscreen->SetPixel(0, 0, 100, 100, 100);
    
    for(;;){
        for(uint8_t i = 0; i < 32; i++){
            for(uint8_t j = 0; j < 64; j++){
            matrix->SetPixel(j, i, 100, 100, 100);
            matrix->SwapOnVSync(offscreen);
            delay(1);
                
            }
        }
        
        // Waiting for data
        // serv_socket.receive();
    }
}

