#include <iostream>
#include <wiringPi.h>

#include "udp_frame.h"
#include "udp_low.h"
#include "rpi-rgb-led-matrix/include/led-matrix.h"
#include "matrix_helper.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// Socket object recieving data
UDPFrame serv_socket; 

MatrixHelper matrix_helper; 

void run_main_loop(void);

int main(int argc, char *argv[]){
    
    // UDP SOCKET BEGIN // 
    serv_socket.begin(5050);
    // UDP SOCKET END //

    // MATRIX SETUP BEGIN // 
    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;

    if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
        
    }
    rgb_matrix::RGBMatrix *matrix =  rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                            runtime_opt);
    // Attach pointere to the matrix for the matrix helper task 
    matrix_helper.Begin(matrix);

    // Attach the socket to our matrix helper class
    matrix_helper.AttachSocket(&serv_socket);
    
    // MATRIX SETUP END // 
    
    // Actual main function here. 
    run_main_loop();
    
    // Not sure how we would get here, but just because. 
    return 1; 
}


void run_main_loop(void){
    for(;;){
        // Waiting for a new packet of data. 
        serv_socket.receive();
            
        // If there is new frame data. Then let's 
        // Tell our matrix helper to send out the data. 
        if(serv_socket.NewMatrixFrame())
            matrix_helper.GetFrame();
        
        // If there is new text data. 
        // Then let's tell our matrix helper to send 
        // out the data. 
        if(serv_socket.NewMatrixText())
            matrix_helper.GetText();
    }
}

