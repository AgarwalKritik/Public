// KRITIK AGARWAL - CS23MTECH11009

/* Hand Cricket with the client
   The client chooses a number between 1-6. The server generates a random number between 1-6. If the numbers match, then the client loses a wicket.
   Else the client gains that many runs. The server keeps track of the score and informs the client after every ball. */

// Include the required header files.
#include <iostream>     // header for standard i/o stream.
#include <unistd.h>     // header for POSIX OS API.
#include <string.h>     // header for string manipulation functions.
#include <sys/socket.h> // header for socket programming in UNIX.
#include <netinet/in.h> // header for defining IP addresses and protocols.
#include <arpa/inet.h>  // header for manipulating IP addresses.
#include <netdb.h>      // header for hostname resolution and network DB access.

// Declaring constants
constexpr int PORT = 12128;

using namespace std;

// Function to handle the client connection.
void handleClient(int cliSock)
{
    int runs = 0;
    int wicket = 0;
    char buff[1024]; // Buffer to store the message received from the client.
    while (true)
    {
        // Generate a random number between 1-6 (both included).
        int nRand = rand() % 6 + 1;
        memset(buff, 0, sizeof(buff));

        // Receive the message from the client.
        ssize_t recvLen = recv(cliSock, buff, sizeof(buff), 0);
        if (recvLen < 0)
        {
            cerr << "<!> Failed to receive data..." << endl; // Display an error message if receiving fails.
            break;
        }
        else if (recvLen == 0)
        {
            cout << "<~> Client disconnected..." << flush << endl;
            break;
        }

        // Convert the message to an integer.
        int message = atoi(buff);
        cout << "\n<~> Client choose: " << message << endl;

        // If the client chooses -1, then the game is over.
        if (message == -1)
        {
            cout << "<!> Client disconnected..." << flush << endl;
            break;
        }

        // Display the server generated random number.
        cout << "< > Server Generated: " << nRand << endl;

        // If the numbers match, then the client loses a wicket.
        if (nRand == message)
        {
            wicket++;

            // If the client loses all the wickets, then the game is over.
            if (wicket == 10)
            {
                cout << "<!> Wicket: 10/10, All Out! Game Over!" << endl;
                snprintf(buff, sizeof(buff), "Game Over: All out! Overall Score: %d", runs);
                string msg(buff);
                send(cliSock, msg.c_str(), msg.size(), 0);
                break;
            }

            // Otherwise, Server responds with the wicket count and the score.
            else
            {
                cout << "<!> WICKET! " << wicket << "/10" << endl;
                snprintf(buff, sizeof(buff), "OUT!! -> Wicket: %d/10 | Score: %d - %d", wicket, runs, wicket);
                string msg(buff);
                send(cliSock, msg.c_str(), msg.size(), 0);
                continue;
            }
        }

        // Otherwise, Server responds with the runs gained.
        else
        {
            runs += message;
            cout << "<+> Client gained runs: " << runs << endl;
            snprintf(buff, sizeof(buff), "Score: %d - %d", runs, wicket);
            string msg(buff);
            send(cliSock, msg.c_str(), msg.size(), 0);
        }
    }

    // Close the client socket.
    close(cliSock);
}

// Driver Function: Program execution begins here...
int main()
{
    system("clear");

    // Initialization
    int srvSock, srvConn;
    sockaddr_in srvAddr, cliAddr;
    socklen_t addrLen;
    char host[NI_MAXHOST];    // Buffer to store the hostname.
    char service[NI_MAXSERV]; // Buffer to store the service (port).

    memset(host, 0, NI_MAXHOST);    // Initialize the host buffer with zeros.
    memset(service, 0, NI_MAXSERV); // Initialize the service buffer with zeros.

    // TCP socket creation and verification
    srvSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /* -> Domain: AF_INET is used as we are using IPv4 Domain.
                                                            -> Type: STREAM socket as our program is using TCP.
                                                            -> Protocol: TCP */
    if (srvSock < 0)
    {
        cerr << "<!> Failed creating socket..." << endl; // Display an error message if socket creation fails.
        exit(EXIT_FAILURE);
    }
    else
        cout << "<~> Socket created successfully..." << endl;

    // Setting up the server address and port.
    memset(&srvAddr, 0, sizeof(srvAddr)); // Initialize the server address with zeros.
    srvAddr.sin_family = AF_INET;         // Setting the domain as IPv4.
    srvAddr.sin_port = htons(PORT);       // Setting the port number.
    srvAddr.sin_addr.s_addr = INADDR_ANY; // Setting the IP address.

    // Binding the socket to the server address.
    if (bind(srvSock, reinterpret_cast<sockaddr *>(&srvAddr), sizeof(srvAddr)) < 0)
    {
        cerr << "<!> Failed binding socket..." << endl; // Display an error message if binding fails.
        close(srvSock);                                 // Close the server socket.
        exit(EXIT_FAILURE);
    }
    else
        cout << "<~> Socket bound successfully..." << endl;

    // Listening the socket and verification.
    if (listen(srvSock, 0) < 0)
    {
        cerr << "<!> Failed listening socket..." << endl; // Display an error message if listening fails.
        close(srvSock);                                   // Close the server socket.
        exit(EXIT_FAILURE);
    }
    else
        cout << "<~> Server is Live. TCP server is listening for connections..." << endl;

    // Accepting the connection
    addrLen = sizeof(cliAddr);
    while (true)
    {
        // Accept a client connection and store the socket.
        srvConn = accept(srvSock, reinterpret_cast<sockaddr *>(&cliAddr), &addrLen);
        if (srvConn < 0)
        {
            cerr << "<!> Failed to accept connection..." << endl; // Display an error message if accepting fails.
            close(srvSock);                                       // Close the server socket.
            exit(EXIT_FAILURE);
        }
        else
        {
            // Determine client's host and service (port)
            if (getnameinfo(reinterpret_cast<sockaddr *>(&cliAddr), addrLen, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
                cout << "<~> " << host << " connected on port " << service << endl;
            else
            {
                inet_ntop(AF_INET, &cliAddr.sin_addr, host, NI_MAXHOST);
                cout << "<~> " << host << " connected on port " << ntohs(cliAddr.sin_port) << endl;
            }

            // Handle the client connection.
            handleClient(srvConn);
            break;
        }
    }

    // Close the socket.
    cout << "<~> Server shutting down..." << endl;
    close(srvSock);
    return 0;
}