import socket

HOST = "127.0.0.1"
PORT = 65400

def init_server():
    while True:
        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
            s.bind((HOST,PORT))
            s.listen()
            conn,addr = s.accept()
            
            with conn:
                print(f"Connected by {addr}")
                while True:
                    data = conn.recv(1024)
                    print(data.decode())
                    if (data.decode() == "/exit"):
                        return
                    if (data.decode() == "/ping"):
                        conn.sendall(b"pong")
                    if not data:
                        break
                    conn.sendall(data)
                    
if __name__ == "__main__":
    init_server()