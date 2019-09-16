#ifndef _MATRIX_HELPER_H
#define _MATRIX_HELPER_H

#include <iostream>
#include <wiringPi.h>

#include "udp_frame.h"
#include "udp_low.h"
#include "rpi-rgb-led-matrix/include/led-matrix.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

class MatrixHelper{
public:
    // Attach a matrix passthrough handler to the matrix
    void Begin(rgb_matrix::RGBMatrix *matrix_passthrough);
    
    // Attach a socket to the Matrix helper
    void AttachSocket(UDPFrame *serv_socket);
    
    // Take's latest packet from the UDP socket, and turn's it into a matrix frame!
    void GetFrame(void);
    // Take's latest packet data from UDP socket, and turns it into scrowling text. 
    void GetText(void);
private:
    rgb_matrix::RGBMatrix *matrix;
    rgb_matrix::FrameCanvas *offscreen;
    UDPFrame *server_socket; 
};

#endif 
