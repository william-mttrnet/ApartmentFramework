import socket
import time 

TCP_IP = 'localhost'
TCP_PORT = 5005
BUFFER_SIZE = 65000
MSG = "Hello Wo;sldkfl;kjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjasdfasdf;lkjsa;dlfkjasldkfj;laskdf;laskdfja;lskdfj;lsakdfj;aslkdfg;rld!"

tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp.connect((TCP_IP, TCP_PORT))

x = 0
time.sleep(1)
while 1: 
    print("sending message!")
    tcp.send(MSG.encode())
    time.sleep(1)


tcp.close()