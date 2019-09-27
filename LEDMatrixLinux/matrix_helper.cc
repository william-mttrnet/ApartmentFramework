#include "matrix_helper.h"
#include "stdlib.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

void MatrixHelper::Begin(rgb_matrix::RGBMatrix *matrix_passthrough){
    // Pass in the matrix, and set it to desired defaults. 
    this->matrix = matrix_passthrough;
    this->matrix->SetBrightness(100);
    this->matrix->Clear();
    
    // Create a frame for animation buffers. 
    this->offscreen = matrix->CreateFrameCanvas();
    this->offscreen->Clear();
    
    // Matrix object creation
    if (this->matrix == NULL)
        printf("Matrix could not be setup :( a fatal error has occoured");
    
    // Setting the whole matrix black just as a starter frame
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(j, i, 7 * i, 255 - 7*i, 2 * i);
            delay(1);
        }
    }
    
}

void MatrixHelper::AttachSocket(UDPFrame *serve_socket){
    this->server_socket = serve_socket;
}

void MatrixHelper::GetFrame(void){
    for(uint32_t i = 0; i < 2048; i++){
        this->offscreen->SetPixel(i%64, 31 - uint32_t(i/64), this->server_socket->in_array[i * 3 + 4], this->server_socket->in_array[i * 3 + 5], this->server_socket->in_array[i * 3 + 6]);
    }
    this->matrix->SwapOnVSync(offscreen);
}

void MatrixHelper::GetText(void){
    // TODO
}

void MatrixHelper::cdl_animate(void){
    
    // Setting the whole matrix black just as a starter frame
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(j, i, 255 - (3 * j), 255 - (4 * j), 255 - j/2);
            delay(1);
        }
    }
    
    delay(6000);
    
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(rand() % 64, rand() % 32, rand() % 255, rand() % 255, rand() % 255);
            delay(1);
        }
    }
    
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(j, i, 255 - (6 * i), 255 - (8 * i), 255 - i);
            delay(1);
        }
    }
    
    delay(6000);
    
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(j, i, 255 - (4 * j), 255 - (4 * j), 255 - j);
            delay(1);
        }
    }
    
    delay(6000);
    
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(j, i, rand() % 255, rand() % 255, rand() % 255);
            delay(1);
        }
    }
    
    for(uint8_t i = 0; i < 32; i++){
        for(uint8_t j = 0; j < 64; j++){
            this->matrix->SetPixel(j, i, 7 * i, 255 - 7*i, 2 * i);
            delay(1);
        }
    }
    
    delay(6000);

}
