import socket
from datetime import date

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
                    elif (data.decode() == "/ping"):
                        conn.sendall(b"pong")
                    elif(data.decode() == "/help"):
                        rmsg = """
==== COMANDOS ====
    - /help : Muestra los comandos
    - /exit : Termina la conexión y cierra el servidor.
    - /ping : Devuelve un mensaje de vuelta
    - /time : Regresa la hora
                        """
                        conn.sendall(rmsg.encode())
                    elif (data.decode() == "/time"):
                        today = date.today()
                        d1 = today.strftime("%d/%m/%y")
                        conn.sendall(d1.encode())
                    if not data:
                        break
                    conn.sendall(data)
                    
if __name__ == "__main__":
    init_server()