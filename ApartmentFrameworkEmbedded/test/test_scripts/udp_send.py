import socket
import time

UDP_IP = "192.168.7.2"
UDP_PORT = 5005

MESSAGE = "What are you doing?"

# Generating a UDP socket.
sending_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while(1):
    print("Sending a packet!")
    sending_socket.sendto(bytearray(MESSAGE, 'utf-8'), (UDP_IP, UDP_PORT))
    time.sleep(1)