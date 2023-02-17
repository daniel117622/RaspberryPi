import socket
import time
HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 65400  # The port used by the server


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    while True:
        msg = input("-> ")
        if (msg == "/exit"):
            print("Exiting server...")
            s.sendall(msg.encode())
            time.sleep(1)
            exit(0)
        try:
            s.sendall(msg.encode())
            data = s.recv(1024)
            print(data.decode())
        except Exception as e:
            print(e)

