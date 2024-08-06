// KRITIK AGARWAL - CS23MTECH11009

/* This program implements a TCP server that receives a ping message from a client, capitalizes it, and sends it back to the client.
   -> The server is capable of handling single client connection.
   -> It is implemented using the socket API of the Linux operating system.
   -> It runs on port 12121.
   -> Randomly generate numbers between 0-11 and drops packets for number generated between 0-3. */

// Include the required header files.
#include <iostream>     // header for standard i/o stream.
#include <unistd.h>     // header for POSIX OS API.
#include <string.h>     // header for string manipulation functions.
#include <sys/socket.h> // header for socket programming in UNIX.
#include <netinet/in.h> // header for defining IP addresses and protocols.
#include <arpa/inet.h>  // header for manipulating IP addresses.
#include <netdb.h>      // header for hostname resolution and network DB access.
#include <fstream>      // header for file stream.

// Declaring constants
constexpr int PORT = 12121;

using namespace std;

// Function to capitalize the message string.
string capitalizeMsg(const string &str)
{
    string result = str;
    for (char &c : result)
        c = toupper(c);
    return result;
}

// Function to handle the client connection.
void handleClient(int cliSock, ofstream &Fout)
{
    char buff[1024]; // Buffer to store the message received from the client.
    while (true)
    {
        // Generate a random number between 0-11 (both included).
        int nRand = rand() % 12;
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

        // Convert the received message to string and then capitalize it.
        string message(buff, recvLen);
        Fout << "\n<~> Message from Client: " << message << endl; // Write the message to the output file.
        Fout.flush();                                             // Flush the buffer to ensure data is written immediately.

        string capitalizedMsg = capitalizeMsg(message);

        // If nRand is between 0-3, then drop the packet.
        if (nRand < 4)
        {
            Fout << "<!> Dropping the Packet... Random Number: " << nRand << " is less than 4." << endl;
            Fout.flush(); // Flush the buffer to ensure data is written immediately.
            continue;
        }

        // Otherwise, Server responds and sends the capitalized message to the client.
        else
        {
            send(cliSock, capitalizedMsg.c_str(), capitalizedMsg.size(), 0);
            Fout << "<?> Sending to Client: " << capitalizedMsg << endl;
            Fout.flush(); // Flush the buffer to ensure data is written immediately.
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

            // File to store the output of the responses between server and client.
            string oFname = string(host) + "_" + string(service) + ".txt";
            ofstream Fout(oFname, ios::out | ios::app);

            // Open the output file.
            if (!Fout.is_open())
            {
                cerr << "<!> Failed to open output file..." << endl; // Display an error message if opening fails.
                return EXIT_FAILURE;
            }

            // Handle the client connection.
            handleClient(srvConn, Fout);
            Fout.close();
            break;
        }
    }

    // Close the socket.
    cout << "<~> Server shutting down..." << endl;
    close(srvSock);
    return 0;
}
