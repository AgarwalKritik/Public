// KRITIK AGARWAL - CS23MTECH11009

/* This program implements a TCP client that sends a ping message to a server and receives a response.
   -> It is implemented using the socket API of the Linux operating system.
   -> It runs on port 12121.
   -> If the server doesn't respond within 1 second, the it considers the packet as lost.
   -> It also calculates and displays statistics such as the minimum, maximum, and average RTT, and the packet loss rate. */

// Include the required header files
#include <iostream>     // Header for standard input/output stream
#include <unistd.h>     // Header for POSIX operating system API
#include <string.h>     // Header for string manipulation functions
#include <sys/socket.h> // Header for socket programming in UNIX
#include <sys/time.h>   // Header for time-related functions
#include <netinet/in.h> // Header for defining IP addresses and protocols
#include <arpa/inet.h>  // Header for manipulating IP addresses
#include <netdb.h>      // Header for hostname resolution and network database access
#include <float.h>      // Header for floating-point types (DBL_MAX)
#include <chrono>       // Header for time-related functions
#include <iomanip>      // Header for input/output manipulators
#include <vector>       // Header for vector container
#include <regex>        // Header for regular expressions

using namespace std;

// Declaring constants
constexpr int PORT = 12121;
constexpr const char *IP = "172.31.0.4";

// Structure to store the ping result
struct PingResult
{
    double rtt;
    string response;
    bool timedOut;
};

// Function to send a ping message to the server
PingResult tcpPinger(int cliSock, const sockaddr_in &srvAddr, int seqNum)
{
    char buff[1024];
    long int currTime = chrono::system_clock::to_time_t(chrono::system_clock::now()); // Get the current time in epoch format (seconds since 1st Jan 1970)

    // Construct the ping message
    snprintf(buff, sizeof(buff), "ping %d %ld", seqNum, currTime);
    string msg(buff);

    // Measuring the start time
    struct timeval start, end;
    gettimeofday(&start, nullptr);

    // Send the ping message to the server
    if (send(cliSock, msg.c_str(), msg.size(), 0) < 0)
    {
        cerr << "<!> Failed to send packet: " << strerror(errno) << endl;
        return {0, "", false};
    }

    // Set the timeout for receiving the response (1 second)
    struct timeval tout;
    tout.tv_sec = 1;
    tout.tv_usec = 0;
    setsockopt(cliSock, SOL_SOCKET, SO_RCVTIMEO, &tout, sizeof(tout));

    // Receive the response from the server
    char resp[1024];
    int totalRecvLen = 0;
    string totalResp;
    int recvLen = recv(cliSock, resp, sizeof(resp), 0);
    gettimeofday(&end, nullptr);

    if (recvLen < 0)
    {
        cerr << "<!> Request timed out! Retrying..." << endl;
        return {0, "", true};
    }

    // Concatenate the received response
    totalResp += string(resp, recvLen);
    double rtt = (end.tv_sec - start.tv_sec) + (static_cast<double>(end.tv_usec - start.tv_usec) / 1e6);

    // Tokenize the received response using regex
    regex pingRegex("PING (\\d+) (\\d+)");
    smatch equals;
    vector<string> resps;
    string respString(totalResp);

    while (regex_search(respString, equals, pingRegex))
    {
        if (equals.size() == 3)
        {
            string response = equals[0];
            resps.push_back(response);
            respString = equals.suffix().str();
        }
    }

    // Process and display each tokenized response
    for (const string &response : resps)
        cout << "< > " << response << ", RTT: " << fixed << setprecision(6) << rtt << " seconds" << endl;

    // Return the last received response's RTT
    return {rtt, resps.empty() ? "" : resps.back(), false};
}

// Function to display the ping statistics
void displayStats(const vector<PingResult> &results)
{
    int nPkts = results.size();
    int nRcvd = 0;
    double totalRTT = 0;
    double minRTT = DBL_MAX;
    double maxRTT = 0;
    int pktLoss = 0;

    // Calculating the statistics
    for (const auto &result : results)
    {
        if (!result.timedOut)
        {
            nRcvd++;
            totalRTT += result.rtt;
            minRTT = min(minRTT, result.rtt);
            maxRTT = max(maxRTT, result.rtt);
        }
        else
            pktLoss++;
    }

    double pktLossRate = (static_cast<double>(pktLoss) / nPkts) * 100;

    // Displaying the statistics
    cout << "\n---- ping statistics ----" << endl;
    cout << "Packets transmitted : " << nPkts << ", Lost & retransmitted : " << nPkts - nRcvd << " (" << setprecision(2) << pktLossRate << "\% loss)" << endl;
    if (nRcvd > 0)
        cout << "RTT min/avg/max = " << setprecision(6) << minRTT << "/" << totalRTT / nRcvd << "/" << maxRTT << " seconds" << endl;
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
    cout << "<~> Connected to the server..." << endl;

    // Reading input from user
    int nPings;
    cout << "<@> Enter the number of pings to send: ";
    cin >> nPings;

    // Send the ping messages to the server
    vector<PingResult> results;
    for (int i = 1; i <= nPings; ++i)
        results.push_back(tcpPinger(cliSock, srvAddr, i));

    // Display the statistics
    displayStats(results);

    // Close the socket
    close(cliSock);
    return 0;
}
