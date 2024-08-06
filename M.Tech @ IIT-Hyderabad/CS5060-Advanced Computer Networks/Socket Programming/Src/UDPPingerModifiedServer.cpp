// KRITIK AGARWAL - CS23MTECH11009

/* This program implements a UDP server that receives a ping message from a client, capitalizes it, and sends it back to the client.
   -> The server is capable of handling multiple client connections concurrently.
   -> It is implemented using the socket API of the Linux operating system.
   -> It runs on port 12120. */

// Include the required header files.
#include <iostream>     // header for standard i/o stream.
#include <unistd.h>     // header for POSIX OS API.
#include <string.h>     // header for string manipulation functions.
#include <sys/socket.h> // header for socket programming in UNIX.
#include <netinet/in.h> // header for defining IP addresses and protocols.
#include <arpa/inet.h>  // header for manipulating IP addresses.
#include <netdb.h>      // header for hostname resolution and network DB access.
#include <fstream>      // header for file stream.
#include <signal.h>     // header for signal handling.

// Declaring constants
constexpr int PORT = 12120;

using namespace std;

// Global variables
volatile sig_atomic_t servLive = 1;
int srvSock = -1;

// Signal handler function to handle Ctrl+C (SIGINT)
void handleSigInt(int signum)
{
    if (signum == SIGINT)
    {
        cout << "<~> CTRL+C pressed..." << endl;
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

// Driver Function: Program execution begins here...
int main()
{
    // Set the packet loss to 33% using the Linux Traffic Control (tc) command.
    system("clear");
    system("sudo tc qdisc add dev eth0 root netem loss 33%");
    cout << "<$> Packet loss of ~33\% set for NIC Level..." << endl;

    // Initialization
    struct sockaddr_in srvAddr, cliAddr;
    socklen_t addrSize = sizeof(cliAddr);

    // UDP socket creation and verification
    srvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); /* -> Domain: AF_INET is used as we are using IPv4 Domain.
                                                           -> Type: DATAGRAM socket as our program is using UDP (connectionless protocol)
                                                           -> Protocol: UDP */
    if (srvSock < 0)
    {
        cerr << "<!> Failed opening socket..." << endl;
        exit(EXIT_FAILURE);
    }

    // Setting up the server address and port.
    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(PORT);
    srvAddr.sin_addr.s_addr = INADDR_ANY;

    // Binding the socket to the server address.
    if (bind(srvSock, reinterpret_cast<sockaddr *>(&srvAddr), sizeof(srvAddr)) < 0)
    {
        cerr << "<!> Failed binding socket..." << endl;
        close(srvSock);
        exit(EXIT_FAILURE);
    }
    else
        cout << "<~> Socket bound successfully..." << endl;

    // Printing a message once the server is started.
    cout << "<~> Server is Live. UDP Ping server is listening for requests..." << endl;

    // Set up the signal handler for Ctrl+C (SIGINT)
    signal(SIGINT, handleSigInt);

    while (servLive)
    {
        if (servLive == 0)
            break;

        char msg[1024];
        memset(msg, 0, sizeof(msg));

        // Receiving the client packet along with the address it is coming from.
        ssize_t recvLen = recvfrom(srvSock, msg, sizeof(msg), 0, reinterpret_cast<sockaddr *>(&cliAddr), &addrSize);
        if (recvLen < 0)
        {
            cerr << "<!> Failed to receive packet..." << endl;
            continue;
        }

        string message(msg, recvLen);

        string capitalizedMsg = capitalizeMsg(message);

        // The server responds.
        sendto(srvSock, capitalizedMsg.c_str(), recvLen, 0, (struct sockaddr *)&cliAddr, addrSize);
    }

    // Close the server socket.
    system("sudo tc qdisc del dev eth0 root netem");
    cout << "<$> Packet loss reset to 0\%..." << endl;
    cout << "<~> Server shutting down..." << endl;
    close(srvSock);
    return 0;
}
