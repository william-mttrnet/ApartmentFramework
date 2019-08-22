import time 
import socket

class LEDStrip:
    def __init__(self, strip_num, num_leds, socket, ip, port):
        # Which strip are we sending data to?
        self.strip_num = strip_num

        # How many LEDs are we controlling?
        self.num_leds = num_leds
        
        # Socket reference and device information
        self.socket = socket
        self.port = port
        self.ip = ip

        # Just an array 
        self.led_array = [0] * 3 * self.num_leds
        # Strip configuration array
        self.strip_setup_arr = [16, 16, 16, int(strip_num)]

    def set_led(self, r, g, b, i):
        # Just setting values of the array to
        # be sent out to the 
        self.led_array[i * 3] = r
        self.led_array[i * 3 + 1] = g
        self.led_array[i * 3 + 2] = b
    
    def send_dat(self):
        # Send the data over UDP
        self.socket.sendto(bytearray(self.strip_setup_arr + self.led_array), (self.ip, self.port))