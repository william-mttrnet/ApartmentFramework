import socket
import time

TCP_IP = 'localhost'
TCP_PORT = 5005
BUFFER_SIZE = 65000

tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp.bind((TCP_IP, TCP_PORT))

tcp.listen(1)

conn, addr = tcp.accept()

print ('Connection address:', addr)
while 1:
    data = conn.recv(BUFFER_SIZE)
    if not data:
        break
    print("received data:", data)
    conn.send(data)  # echo
    time.sleep(.01)
    

conn.close()