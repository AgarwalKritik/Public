// KRITIK AGARWAL - CS23MTECH11009

/* Hand Cricket with the server
   The client chooses a number between 1-6. The server generates a random number between 1-6. If the numbers match, then the client loses a wicket.
   Else the client gains that many runs. The server keeps track of the score and informs the client after every ball. */

// Include the required header files
#include <iostream>     // Header for standard input/output stream
#include <unistd.h>     // Header for POSIX operating system API
#include <string.h>     // Header for string manipulation functions
#include <sys/socket.h> // Header for socket programming in UNIX
#include <sys/time.h>   // Header for time-related functions
#include <netinet/in.h> // Header for defining IP addresses and protocols
#include <arpa/inet.h>  // Header for manipulating IP addresses
#include <netdb.h>      // Header for hostname resolution and network database access
#include <regex>        // Header for regular expressions

using namespace std;

// Declaring constants
constexpr int PORT = 12128;
constexpr const char *IP = "127.0.0.1";

// Function to send and receive messages from the server
void tcpCricket(int cliSock, const sockaddr_in &srvAddr)
{
    int num;
    char buff[1024];
    while (true)
    {
        // Ask the user to enter a number between 1-6
        cout << "\n<@> Enter a number between 1-6: ";
        cin >> num;

        // Check if the number is -1
        if (num <= -1)
        {
            cout << "<*> Quitting the game..." << endl;
            break;
        }

        // Check if the number is valid
        else if (num > 6 || num == 0)
        {
            cout << "<!> Invalid Entry!" << endl;
            continue;
        }

        // Construct the message
        snprintf(buff, sizeof(buff), "%d", num);
        string msg(buff);

        // Send the message to the server
        if (send(cliSock, msg.c_str(), msg.size(), 0) < 0)
        {
            cerr << "<!> Failed to send packet: " << strerror(errno) << endl;
            break;
        }

        // Receive the response from the server
        char resp[1024];
        int recvLen = recv(cliSock, resp, sizeof(resp), 0);
        if (recvLen < 0)
        {
            cerr << "<!> Packet Lost! Retrying..." << endl;
            continue;
        }

        // Check if the game is over
        regex pingRegex("Game Over: All out! Overall Score: (\\d+)");
        smatch equals;
        string respString(resp);

        // Display the response from the server
        resp[recvLen] = '\0';
        cout << "< > Server: " << resp << endl;

        // If the game is over, then break the loop
        if (regex_search(respString, equals, pingRegex))
            break;
    }

    // Close the socket
    close(cliSock);
}

// Driver Function: Program execution begins here
int main()
{
    system("clear");

    // Initialization
    int cliSock;
    sockaddr_in srvAddr;

    // Server address and port, initializing the srvAddr structure to zeros
    memset(&srvAddr, 0, sizeof(srvAddr));
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(PORT);
    srvAddr.sin_addr.s_addr = inet_addr(IP);

    // TCP socket creation and verification
    cliSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Domain: AF_INET is used for IPv4 Domain, Type: STREAM socket for TCP, Protocol: TCP
    if (cliSock < 0)
    {
        cerr << "<!> Failed creating socket : " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    cout << "<~> Socket created successfully..." << endl;

    // Establishing a connection to the server
    if (connect(cliSock, reinterpret_cast<struct sockaddr *>(&srvAddr), sizeof(srvAddr)) < 0)
    {
        cerr << "<!> Failed to connect to the server : " << strerror(errno) << endl;
        close(cliSock);
        exit(EXIT_FAILURE);
    }

    // Play the game
    cout << "<~> Connected to the server..." << endl;
    cout << "<~> The game is on!" << endl;
    tcpCricket(cliSock, srvAddr);

    // Close the socket
    cout << "<x> Connection Closed." << endl;
    close(cliSock);
    return 0;
}