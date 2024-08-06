// KRITIK AGARWAL - CS23MTECH11009

/* This program implements a UDP client that sends a ping message to a server and receives a response.
   -> It is implemented using the socket API of the Linux operating system.
   -> It runs on port 12120.
   -> If the server doesn't respond within 1 second, the it considers the packet as lost.
   -> It also calculates and displays statistics such as the minimum, maximum, and average RTT, and the packet loss rate. */

// Include the required header files
#include <iostream>     // header for standard i/o stream.
#include <unistd.h>     // header for POSIX OS API.
#include <string.h>     // header for string manipulation functions.
#include <sys/socket.h> // header for socket programming in UNIX.
#include <sys/time.h>   // header for time-related functions.
#include <netinet/in.h> // header for defining IP addresses and protocols.
#include <arpa/inet.h>  // header for manipulating IP addresses.
#include <netdb.h>      // header for hostname resolution and network DB access.
#include <float.h>      // header for floating-point types (DBL_MAX)
#include <chrono>       // header for time-related functions.
#include <iomanip>      // header for i/o manipulators.
#include <vector>       // header for vector container.

using namespace std;

// Declaring constants
constexpr int PORT = 12120;
constexpr const char *IP = "172.31.0.4";

// Structure to store the ping result.
struct PingResult
{
    double rtt;
    string response;
    bool timedOut;
};

// Function to send a ping message to the server.
PingResult udpPinger(int cliSock, const sockaddr_in &srvAddr, int seqNum)
{
    char buff[1024];
    long int currTime = chrono::system_clock::to_time_t(chrono::system_clock::now()); // Get the current time in epoch format (seconds since 1st Jan 1970)

    // Construct the ping message
    snprintf(buff, sizeof(buff), "ping %d %ld", seqNum, currTime);
    string msg(buff);

    // Measuring the start time
    struct timeval start, end;
    gettimeofday(&start, nullptr);

    // Sending the ping message to the server
    if (sendto(cliSock, msg.c_str(), msg.length(), 0, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0)
    {
        cerr << "<!> Failed to send packet: " << strerror(errno) << endl;
        return {0, "", false};
    }

    // Setting a timeout for receiving a response (in this case, 1 second)
    struct timeval tout;
    tout.tv_sec = 1;
    tout.tv_usec = 0;
    setsockopt(cliSock, SOL_SOCKET, SO_RCVTIMEO, &tout, sizeof(tout));

    char resp[1024];                                                          // Buffer to store the response from the server.
    int recvLen = recvfrom(cliSock, resp, sizeof(resp), 0, nullptr, nullptr); // Receive the response from the server.
    gettimeofday(&end, nullptr);                                              // Get the current time and store it in the end variable.

    // Check if the response timed out.
    if (recvLen < 0)
    {
        cerr << "<!> Request timed out!" << endl;
        return {0, "", true};
    }
    else
    {
        // Calculating the RTT
        double rtt = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1e6);
        resp[recvLen] = '\0'; // Add a null character at the end of the response string.
        cout << "< > " << resp << ", RTT: " << rtt << " seconds" << endl;
        return {rtt, resp, false};
    }
}

// Function to display the ping statistics.
void displayStats(const vector<PingResult> &results)
{
    int nPkts = results.size();
    int nRcvd = 0;
    double totalRTT = 0;
    double minRTT = DBL_MAX;
    double maxRTT = 0;
    int pktLoss = 0;

    // Calculating the statistics.
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

    // Displaying the statistics.
    cout << "\n---- ping statistics ----" << endl;
    cout << "Packets transmitted : " << nPkts << ", Lost : " << nPkts - nRcvd << " (" << setprecision(2) << pktLossRate << "\% loss)" << endl;
    if (nRcvd > 0)
        cout << "RTT min/avg/max = " << setprecision(6) << minRTT << "/" << totalRTT / nRcvd << "/" << maxRTT << " seconds" << endl;
}

// Driver Function: Program execution begins here...
int main()
{
    system("clear");

    // Initialization
    int cliSock;
    struct sockaddr_in srvAddr;
    socklen_t addrSize = sizeof(srvAddr);

    // UDP socket creation and verification
    cliSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); /* -> Domain: AF_INET is used as we are using IPv4 Domain.
                                                           -> Type: DGRAM socket as our program is using UDP.
                                                           -> Protocol: UDP */
    if (cliSock < 0)
    {
        cerr << "<!> Failed opening socket: " << strerror(errno) << endl; // Display an error message if socket creation fails.
        exit(EXIT_FAILURE);
    }

    // Server address and port, initializing the srvAddr structure to zero.
    memset(&srvAddr, 0, sizeof(srvAddr));    // Initialize the server address with zeros.
    srvAddr.sin_family = AF_INET;            // Setting the domain as IPv4.
    srvAddr.sin_port = htons(PORT);          // Setting the port number.
    srvAddr.sin_addr.s_addr = inet_addr(IP); // Setting the IP address.

    // Reading input from user.
    int nPings;
    cout << "> Enter the number of pings to send : "; // Prompt the user to enter the number of pings to send.
    cin >> nPings;

    // Sending the ping messages to the server.
    vector<PingResult> results;
    for (int i = 1; i <= nPings; ++i)
    {
        PingResult result = udpPinger(cliSock, srvAddr, i);
        results.push_back(result);
    }

    // Displaying the statistics.
    displayStats(results);

    // Close the socket.
    close(cliSock);
    return 0;
}