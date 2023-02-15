Guia de uso

===================== PYTHON ======================

Inicializar server con el comando "python server.py"

Después inicializar el cliente con "python client.py"

Una vez en el cliente, aparecera un prompt para enviar comandos al servidor. 
En caso de que no sea un comando , el mensaje aparecera en la terminal del servidor.
En caso de que sea un comando, el servidor realizara alguna tarea.

Ejemplos de comandos.
    </br>
    - /exit : Termina la conexión y cierra el servidor.
    </br>
    - /ping : Devuelve el mensaje "pong" al cliente.
    </br>
    - /time : Regresa la hora del servidor al cliente.
    </br>
    - /help : Muestra comandos disponibles.

===================== C ======================
</br>
</br>
Inicializar server con el comando "g++ server.cpp y ./server"

Después inicializar el cliente con "gcc client.c y ./client"

Una vez inicializado el servidor y compilado el archivo del cliente, 
se detallara en pantalla que la conexión fue establecida, posteriormente a esto, 
el cliente puede enviar un string al servidor.

===================== THREADS ======================

Utilizar makefile usando el siguiente comando:
</br>
make main N="(numero a incremetar por 5)".

========== C SERVER =============== 
</br>
Compilar json tests
</br>
g++ -w -std=c++11 -pthread -o json_parser json.cpp json_parsing_test.cpp
</br>
Servidor
</br>
g++ -w -std=c++11 -pthread -o server tcp.cpp server.cpp

====================PRUEBA JSON====================
</br>
g++ -std=c++11 example.cpp -o example
./example
