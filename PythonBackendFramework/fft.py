 
import numpy as np
import pyaudio
import threading
import time 

class MatrixFFT:
    def __init__(self, sample_size, rate):
        self.sample_size = sample_size
        self.rate = rate 
        
        self.pyaudio_instance = pyaudio.PyAudio()
        self.stream = None
        
        self.latest_raw_read = None 
        self.latest_fft_read = None
        
    def begin(self):
        # Setup stream 
        self.stream = self.pyaudio_instance.open(format=pyaudio.paInt16,channels=1,rate=self.rate, input=True, frames_per_buffer=self.sample_size)
        
    def end(self):
        # DESTRUCTOR
        self.stream.stop_stream()
        self.stream.close()
        self.pyaudio_instance.terminate()
        
    def capture_audio(self):
        self.latest_raw_read = abs(np.fromstring(self.stream.read(self.sample_size, exception_on_overflow = False), dtype=np.int16))
    
    def proccess_fft(self):
        # Usese Numpy to create an fft read. 
        self.latest_fft_read = abs(np.fft.fft(self.latest_raw_read).real)

    @property
    def data(self):
        return self.latest_fft_read
    
    
