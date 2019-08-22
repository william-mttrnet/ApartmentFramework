import time
import socket

import led_control


strip_one = None
UDP_IP = "192.168.7.2"
UDP_PORT = 5005

sending_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
strip_one = led_control.LEDStrip(1, 144, sending_socket, UDP_IP, UDP_PORT)

while(1):
    # Updating LEDs
    strip_one.send_dat()
    time.sleep(1)