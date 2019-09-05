from samplebase import SampleBase
from rgbmatrix import graphics 
import time 
import socket

UDP_IP = "localhost" 
UDP_PORT = 5050
UDP_MAX_SIZE = 32,768
socket = None 

class RunUDP(SampleBase):
    def __init__(self, *args, **kwards):
        super(RunText, self).__init__(*args, **kwargs)
        
        # setting up our localhost socket. 
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(UDP_IP, UDP_PORT)
        
    def run(self):
        message = self.sock.recvfrom(UDP_MAX_SIZE)
        data = message[0]
        
        for n in range(len(data)):
            pass 
        
        offscreen_canvas = self.matrix.CreateFrameCanvas()
        
        offscreen_canvas = self.matrix.SwapOnVSync(offscreen_canvas)
        time.sleep(.001)
