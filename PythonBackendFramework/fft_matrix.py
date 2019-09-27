from matrix import UDPMatrix
import numpy as np
import pyaudio
import threading
import time 
from fft import MatrixFFT

fft_handler = MatrixFFT(256, 44100)
fft_handler.begin()

matrix = UDPMatrix('localhost', 5050)
matrix.begin()

sound_arr = [0] * 64
interval = 0

decrement_val = 1

while(1):
    fft_handler.capture_audio()
    fft_handler.proccess_fft()
    
    interval = interval + 1
    time.sleep(.01)
    interval = 0
    for i in range(64):
        if sound_arr[i] < 0: 
            sound_arr[i] = 0 
            
        if sound_arr[i] >= 24:
            sound_arr[i] = sound_arr[i] - 3 * decrement_val
        
        if sound_arr[i] < 24 and sound_arr[i] > 11:
            sound_arr[i] = sound_arr[i] - 2 * decrement_val
            
        else:
            sound_arr[i] = sound_arr[i] - 1 * decrement_val

    for x in range(64):
        intensity = 0
        if x == 0:
            intensity = int(fft_handler.data[1] / 1500)
        else:
            intensity = int(fft_handler.data[x] / 1500)
        
        if intensity > 31: 
            intensity = 31
        
        if sound_arr[x] < intensity: 
            sound_arr[x] = intensity
        
            
        for y in range(sound_arr[x]):
            matrix.set_led(x, 31-y,  sound_arr[x] * 8, 255 - sound_arr[x] * 8, 0)
        
        for y in range(31 - sound_arr[x]):
            if sound_arr[x] < 0: 
                sound_arr[x] = 0
            matrix.set_led(x, y, sound_arr[x] * 2, sound_arr[x] * 2, sound_arr[x] * 2)
                
    
    matrix.send()
