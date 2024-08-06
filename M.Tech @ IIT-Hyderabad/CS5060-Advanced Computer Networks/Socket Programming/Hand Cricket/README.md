# Hand Cricket with the server

The client should choose a number between 1-6. The server should generate a random number between 1-6. If the numbers match, then the client loses a wicket. Else the client gains that many runs. The server should keep track of the score and inform after every ball.

# How to run?

1. Server

```shell
g++ TCPHandCricketServer.cpp -o TCPHandCricketServer
./TCPHandCricketServer
```
   
2. Client

```shell
g++ TCPHandCricketClient.cpp -o TCPHandCricketClient
./TCPHandCricketClient
```

###### Author: [Kritik Agarwal](https://github.com/Kritik007)
