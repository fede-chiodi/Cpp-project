# NETWORK PROJECT
## CLIENT-SERVER WITH TCP AND IPv4 PROTOCOL

In this folder there is a simple client-server system, where some clien can send a message to the main server.

If you want to try it, clone the repo and than go to networking directory.
Than you have to start the server first. To do it you have to launch these command from terminal:
```
to compile
g++ src/*.cpp main_server.cpp -o server -pthread
```
```
to execute
./server
```
This will start your server at 127.0.0.1 (localhost) on port 8080


After that you have to start, from another terminal, the client:
```
to compile
g++ src/*.cpp main_client.cpp -o client -pthrea
```
```
to execute
./client
```
You can start more than one client from many terminal. You have always to launch the above command.

When you execute a client it will send a message to the server and will receive from the server a confirmation message

At the end, to close the server, you have to press Ctrl + C and then close the server terminal. In fact you try to send something to the server from a client, it will give you an error message.
