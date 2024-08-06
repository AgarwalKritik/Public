// KRITIK AGARWAL - CS23MTECH11009

/* This program implements a concurrent TCP server that receives a ping message from a client, capitalizes it, and sends it back to the client.
   -> The server is capable of handling multiple client connections concurrently.
   -> It is implemented using the socket API of the Linux operating system.
   -> It runs on port 12121. */

// Include the required header files.
#include <iostream>     // header for standard i/o stream.
#include <unistd.h>     // header for POSIX OS API.
#include <string.h>     // header for string manipulation functions.
#include <sys/socket.h> // header for socket programming in UNIX.
#include <netinet/in.h> // header for defining IP addresses and protocols.
#include <arpa/inet.h>  // header for manipulating IP addresses.
#include <netdb.h>      // header for hostname resolution and network DB access.
#include <pthread.h>    // header for multi-threading (concurrency) support.
#include <signal.h>     // header for signal handling.

// Declaring constant
constexpr int PORT = 12121;

using namespace std;

// Global variables
volatile sig_atomic_t servLive = 1;
int srvSock = -1;

// Signal handler function to handle Ctrl+C (SIGINT)
void handleSigInt(int signum)
{
    if (signum == SIGINT)
    {
        cout << "<~> CTRL+C pressed. Server shutting down..." << endl;
        servLive = 0;
        close(srvSock);
    }
}

// Function to capitalize the message string.
string capitalizeMsg(const string &str)
{
    string result = str;
    for (char &c : result)
        c = toupper(c);
    return result;
}

// Function to handle client connections.
void *handleClient(void *arg)
{
    int cliSock = *((int *)arg); // Get the client socket from the argument.
    delete (int *)arg;           // Delete the dynamically allocated memory for the client socket.

    char buff[1024]; // Buffer to store the message received from the client.
    while (true)
    {
        memset(buff, 0, sizeof(buff));

        // Receive the message from the client.
        ssize_t recvLen = recv(cliSock, buff, sizeof(buff), 0); // Receive data from the client and store the length.
        if (recvLen < 0)
        {
            cerr << "<!> Failed to receive data..." << flush << endl; // Display an error message if receiving fails.
            break;
        }
        else if (recvLen == 0)
        {
            cout << "<~> Client disconnected... Client ID: " << cliSock << flush << endl; // Display a message if the client disconnects.
            break;
        }

        // Convert the received message to string and then capitalize it.
        string message(buff, recvLen);
        string capitalizedMsg = capitalizeMsg(message);

        // Server responds and sends the capitalized message to the client.
        send(cliSock, capitalizedMsg.c_str(), capitalizedMsg.size(), 0);
    }

    // Close the client socket.
    close(cliSock);
    pthread_exit(NULL); // Exit the thread.
}

// Driver Function: Program execution begins here...
int main()
{
    system("clear");

    // Set the packet loss to 33% using the Linux Traffic Control (tc) command.
    system("sudo tc qdisc add dev eth0 root netem loss 33%");
    cout << "<$> Packet loss of ~33\% set for NIC Level..." << endl;

    // Intialization
    sockaddr_in srvAddr, cliAddr;
    socklen_t addrLen;
    char host[NI_MAXHOST];    // Hostname of the client.
    char service[NI_MAXSERV]; // Service (port) of the client.

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

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

    // Set the server address and port.
    memset(&srvAddr, 0, sizeof(srvAddr)); // Initialize the server address structure with zeros.
    srvAddr.sin_family = AF_INET;         // Set the address family to IPv4.
    srvAddr.sin_port = htons(PORT);       // Set the server port number.
    srvAddr.sin_addr.s_addr = INADDR_ANY; // Allow connections on any local network interface.

    // Bind the socket to the server address.
    if (bind(srvSock, reinterpret_cast<sockaddr *>(&srvAddr), sizeof(srvAddr)) < 0)
    {
        cerr << "<!> Failed binding socket..." << endl; // Display an error message if binding fails.
        close(srvSock);                                 // Close the server socket.
        exit(EXIT_FAILURE);
    }
    else
        cout << "<~> Socket bound successfully..." << endl;

    // Listen for connections on the socket.
    if (listen(srvSock, 5) < 0)
    {
        cerr << "<!> Failed listening socket..." << endl; // Display an error message if listening fails.
        close(srvSock);                                   // Close the server socket.
        exit(EXIT_FAILURE);
    }
    else
        cout << "<~> Server is Live. TCP server is listening for connections..." << endl;

    // Set up the signal handler for Ctrl+C (SIGINT)
    signal(SIGINT, handleSigInt);

    // Accept client connections.
    addrLen = sizeof(cliAddr);
    while (servLive)
    {
        if (servLive == 0)
            break;
        // Create a pointer to an integer for the client socket and accept the connection.
        int *srvConn = new int;
        *srvConn = accept(srvSock, reinterpret_cast<sockaddr *>(&cliAddr), &addrLen);
        if (*srvConn < 0)
        {
            cerr << "<!> Failed to accept connection..." << endl; // Display an error message if accepting a connection fails.
            delete srvConn;                                       // Delete the dynamically allocated memory for the client socket.
            continue;
        }
        else
            cout << "<~> Connection accepted successfully... Client ID: " << *srvConn << endl; // Display a success message for accepting a connection.

        // Create a thread to handle the client connections.
        pthread_t tid;
        if (pthread_create(&tid, NULL, handleClient, (void *)srvConn) != 0)
        {
            cerr << "<!> Failed to create thread for client..." << endl; // Display an error message if creating a thread fails.
            close(*srvConn);                                             // Close the client connection.
            delete srvConn;                                              // Delete the dynamically allocated memory for the client socket.
        }
        else
        {
            cout << "    Thread created... '";
            // Determine client's host and service (port)
            if (getnameinfo(reinterpret_cast<sockaddr *>(&cliAddr), addrLen, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
                cout << host << "' connected on port " << service << endl;
            else
            {
                inet_ntop(AF_INET, &cliAddr.sin_addr, host, NI_MAXHOST);
                cout << host << "' connected on port " << ntohs(cliAddr.sin_port) << endl;
            }
        }
    }

    system("sudo tc qdisc del dev eth0 root netem");
    cout << "<$> Packet loss reset to 0\%..." << endl;
    close(srvSock); // Close the server socket.
    return 0;
}