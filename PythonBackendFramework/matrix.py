import socket 
import time

TCP_IP = '192.168.1.7'
TCP_PORT = 5050

class UDPMatrix:
    def __init__(self, ip, port):
        self.tcp = None
        self.out_arr = None
        self.ip = ip
        self.port = port 
    
    # Set the right parts of the array for the LED matrix. 
    def set_led(self, x, y,  r, g, b):
        self.out_arr[4 + 3 * (64 * y + x)] = r
        self.out_arr[5 + 3 * (64 * y + x)] = g
        self.out_arr[6 + 3 * (64 * y + x)] = b
    
    def send(self):
        self.tcp.sendto(bytearray(self.out_arr), (self.ip, self.port))

    # Setup udp connection. 
    def begin(self):
        self.tcp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.tcp.connect((TCP_IP, TCP_PORT))
        self.out_arr = [15] * 4 + [0] * 2050 * 3
        
