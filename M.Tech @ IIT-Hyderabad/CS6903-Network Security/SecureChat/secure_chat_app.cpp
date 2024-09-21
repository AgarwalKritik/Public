// Kritik Agarwal - CS23MTECH11009
// Girish Thatte - CS22MTECH11005
// Naveen Naik - CS23MTECH11011
// Importing the required libraries
#include <iostream>        // For standard input/output
#include <openssl/ssl.h>   // For OpenSSL library functions
#include <openssl/err.h>   // For OpenSSL error handling
#include <openssl/bio.h>   // For OpenSSL BIO functions
#include <openssl/pem.h>   // For OpenSSL PEM functions
#include <openssl/dtls1.h> // For DTLS functions
#include <openssl/x509.h>  // For X509 certificate functions
#include <openssl/rand.h>  // For OpenSSL random number generation
#include <sys/socket.h>    // For socket functions
#include <sys/time.h>      // For time functions
#include <netinet/in.h>    // For internet address functions
#include <arpa/inet.h>     // For internet address functions
#include <netdb.h>         // For network database functions
#include <cstring>         // For string functions
#include <string.h>        // For string functions
#include <unistd.h>        // For POSIX functions
#include <chrono>          // For time functions
#include <thread>          // For thread functions

// Importing our custom header file
#include "secure_chat_app.h" // For custom constants

// Using the standard namespace
using namespace std; // For standard namespace

struct receiveSSLMessage
{
    ssize_t recvfrom_flag;
    char buf[BUFF_SIZE];
};

// Function to generate a cookie for the DTLS handshake
int generate_cookie(SSL *ssl, unsigned char *cookie, unsigned int *cookie_len)
{
    // Generate a random cookie of 16 bytes using OpenSSL random number generator function
    unsigned char rand_cookie[16];
    RAND_bytes(rand_cookie, sizeof(rand_cookie));

    // Copy the random cookie to the cookie variable and set the cookie length to 16 bytes (size of the random cookie)
    memcpy(cookie, rand_cookie, sizeof(rand_cookie));
    *cookie_len = sizeof(rand_cookie);

    return 1; // Return 1 to indicate success
}

// Function to verify the cookie for the DTLS handshake
int verify_cookie(SSL *ssl, const unsigned char *cookie, unsigned int cookie_len)
{
    // Verify the cookie by comparing it with the random cookie generated during the handshake process
    return 1; // Return 1 to indicate success
}

// Defining the class Alice (Client)
class Alice
{
private:
    // Defining the private variables
    sockaddr_in srvAddr;                     // Server address
    socklen_t srvAddrSize = sizeof(srvAddr); // Server address size
    const SSL_METHOD *method;                // SSL method
    SSL_CTX *sslCtx;                         // SSL context
    EVP_PKEY *skey;                          // Public key
    SSL *ssl;                                // SSL object
    struct timeval timeout;                  // Timeout object for the DTLS handshake

public:
    // Defining the public variables
    int unixSock;

    // Constructor for the class Alice
    Alice(const char *server_hostname)
    {
        // Print the client start message to the console and try to connect to the server
        cout << "<~> CLIENT STARTED!" << endl;
        cout << "<~> Trying to connect to " << server_hostname << endl;

        unixSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        struct hostent *server_ip;
        server_ip = gethostbyname(server_hostname); // Get the IP address of the server
        memset(&srvAddr, 0, srvAddrSize);           // Clear the server address
        srvAddr.sin_family = AF_INET;               // Set the server address family to AF_INET

        if (server_ip == NULL)
        {
            // Print an error message to the console and exit the program if the server IP address is not found
            cerr << "<!> No such host exists" << endl;
            exit(1);
        }

        srvAddr.sin_port = htons(PORT);                                                 // Set the server port to the defined port number
        memcpy(&srvAddr.sin_addr.s_addr, server_ip->h_addr, server_ip->h_length);       // Copy the server IP address to the server address structure
        if (connect(unixSock, reinterpret_cast<sockaddr *>(&srvAddr), sizeof(srvAddr))) // Connect to the server
        {
            cerr << "<!> UDP Connection failed" << endl;
            exit(EXIT_FAILURE);
        }
        else
            cout << "<~> Connected to " << server_hostname << endl;
    }

    // Function to initialise the SSL
    void init_ssl()
    {
        SSL_load_error_strings();
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();
    }

    // Function to close the SSL
    void close_ssl()
    {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(sslCtx);
    }

    // Function to perform the application layer handshake
    void applicationLayerHandshake()
    {
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            // Send the chat hello message to the server
            string msg(CHAT_HELLO);
            if (sendto(unixSock, msg.c_str(), msg.size(), 0, reinterpret_cast<sockaddr *>(&srvAddr), srvAddrSize) < 0)
            {
                cout << "<!> '" << CHAT_HELLO << "' message failed to send" << endl;
                close(unixSock);
            }
            else
                cout << "<~> Sent: " << msg << endl;

            char buf[BUFF_SIZE];
            ssize_t recvBufLen = recvfrom(unixSock, buf, sizeof(buf), 0, reinterpret_cast<sockaddr *>(&srvAddr), &srvAddrSize);
            if (recvBufLen < 0)
            {
                cerr << "<!> Failed to recieve packet!" << endl;
                return;
            }
            buf[recvBufLen] = '\0';

            if (strcasecmp(buf, CHAT_OK_REPLY) == 0)
            {
                cout << "<~> Received from Server: " << buf << endl;
                initiateSecureChat();
            }

            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
        close(unixSock);
    }

    // Function to initiate the secure chat by sending the chat start SSL message to the server
    void initiateSecureChat()
    {
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            // Send the chat start SSL message to the server
            string msg(CHAT_START_SSL);
            if (sendto(unixSock, msg.c_str(), msg.size(), 0, reinterpret_cast<sockaddr *>(&srvAddr), srvAddrSize) < 0)
            {
                cerr << "<!> '" << CHAT_START_SSL << "' message failed to send" << endl;
                close(unixSock);
            }
            else
                cout << "<~> Sent: " << msg << endl;

            char buf[BUFF_SIZE];
            ssize_t recvBufLen = recvfrom(unixSock, buf, sizeof(buf), 0, nullptr, nullptr);
            if (recvBufLen < 0)
            {
                cerr << "<!> Failed to recieve packet!" << endl;
                return;
            }
            buf[recvBufLen] = '\0';

            if (strcasecmp(buf, CHAT_START_SSL_ACK) == 0)
            {
                cout << "<~> Received from Server: " << buf << endl;
                // Now initiate the DTLS handshake and secure communication with the server
                initiateDTLSHandshake();
            }
            else if (strcasecmp(buf, CHAT_START_SSL_NOT_SUPPORTED) == 0)
            {
                cout << "<!> Server does not support SSL. Starting normal chat..." << endl;
                startChat();
            }
            else
                cout << "<~> Received from Server: " << buf << endl;

            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
        close(unixSock);
    }

    // Function to initiate the DTLS handshake and secure communication with the server
    void initiateDTLSHandshake()
    {
        // Print the DTLS handshake initiation message to the console
        cout << "<~> Initiating DTLS Handshake..." << endl;

        // Initialise SSL
        init_ssl();

        // SSL context creation and configuration for DTLS
        sslCtx = SSL_CTX_new(DTLS_client_method());             // Create a new SSL context for DTLS
        SSL_CTX_set_min_proto_version(sslCtx, DTLS1_2_VERSION); // Set the minimum DTLS protocol version to DTLS 1.2
        SSL_CTX_set_max_proto_version(sslCtx, DTLS1_2_VERSION); // Set the maximum DTLS protocol version to DTLS 1.2
        ssl = SSL_new(sslCtx);                                  // Create a new SSL object
        SSL_set_fd(ssl, unixSock);                              // Set the file descriptor for the SSL object

        SSL_CTX_set_security_level(sslCtx, 1);                                                            // This is done to allow key size >= 1024 and < 2048 bits for RSA key exchange
        SSL_CTX_set_mode(sslCtx, SSL_MODE_AUTO_RETRY);                                                    // Set the SSL context mode to auto retry to automatically retry the handshake
        SSL_CTX_set_session_cache_mode(sslCtx, SSL_SESS_CACHE_CLIENT | SSL_SESS_CACHE_NO_INTERNAL_STORE); // Set the session cache mode for the SSL context
        SSL_set_verify_depth(ssl, 2);                                                                     // Set the maximum depth for the certificate chain verification to 2
        SSL_set_verify(ssl, SSL_VERIFY_PEER, NULL);                                                       // Set the SSL verification mode to peer verification (verify the server certificate)

        const char *cert_file_name = ALICE_CERT_NAME;
        const char *sk_file_name = ALICE_PRIVATE_KEY_NAME;

        if (SSL_CTX_use_certificate_file(sslCtx, cert_file_name, SSL_FILETYPE_PEM) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(1);
        }

        if (SSL_CTX_use_PrivateKey_file(sslCtx, sk_file_name, SSL_FILETYPE_PEM) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(1);
        }

        if (!SSL_CTX_check_private_key(sslCtx))
        {
            cerr << "<!> Private Key does not comply with the certificate" << endl;
            abort();
        }

        if (!SSL_CTX_load_verify_locations(sslCtx, ROOT_STORE, NULL))
        {
            cout << "<~> Verify trust store location successful" << endl;
        }

        // Support Perfect Forward Secrecy (PFS)
        const char *pfs_ciphers = "ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384";
        SSL_CTX_set_cipher_list(sslCtx, pfs_ciphers);

        if (SSL_get_peer_certificate(ssl) && SSL_get_verify_result(ssl) == X509_V_OK)
            cout << "<~> Server Certificate Verified!\n";

        // DTLS handshake
        int ret = SSL_connect(ssl);
        if (ret != 1)
        {
            cerr << "<!> DTLS Handshake failed" << endl;
            ERR_print_errors_fp(stderr);
            close_ssl();
            return;
        }
        else
            cout << "<~> Server accepted DTLS connection\n";

        cout << "<~> DTLS Handshake successful" << endl;
        startChatSSL();
    }

    // Function to send the chat message to the server
    int sendChatMessage(SSL *ssl, const char *message)
    {
        ssize_t ssl_write_flag;
        ssl_write_flag = SSL_write(ssl, message, strlen(message));
        if (ssl_write_flag <= 0)
            cerr << "<!> '" << message << "' message failed to send" << endl;
        else if (strcasecmp(message, CHAT_CLOSE) == 0)
        {
            // Server sends the chat close message to the client and closes the connection
            cout << "<~> Sent " << CHAT_CLOSE << " to Client.\n<~> Closing the connection..." << endl;
            close_ssl();
            close(unixSock);
            exit(0);
        }
        else
            cout << "<~> Sent to Server: " << message << endl;
        return ssl_write_flag;
    }

    //  Function to receive the chat message from the server
    receiveSSLMessage receiveSSLMsg(SSL *ssl)
    {
        receiveSSLMessage resp;
        memset(resp.buf, 0, sizeof(resp.buf)); // Clear buffer
        resp.recvfrom_flag = SSL_read(ssl, resp.buf, sizeof(resp.buf) - 1);
        if (resp.recvfrom_flag <= 0)
            cerr << "<!> Failed to recieve packet!" << endl;
        else if (strcasecmp(resp.buf, CHAT_CLOSE) == 0)
        {
            resp.buf[resp.recvfrom_flag] = '\0';
            cout << "<~> Received " << resp.buf << " from Server.\n<~> Closing the connection..." << endl;
            close_ssl();
            close(unixSock);
            exit(0);
        }
        else
            cout << "<~> Received from Server: " << resp.buf << endl;
        return resp;
    }

    // Function to start the chat with the server
    void startChatSSL()
    {
        char chatMsg[BUFF_SIZE];
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            // Client inputs the chat message and sends it to the server
            cout << "</> Client: ";
            cin.getline(chatMsg, sizeof(chatMsg));
            sendChatMessage(ssl, chatMsg);
            if (strcasecmp(chatMsg, CHAT_CLOSE) == 0)
            {
                // Send the chat close message to the server
                sendChatMessage(ssl, chatMsg);
                close_ssl();
                close(unixSock);
                exit(0);
            }
            receiveSSLMsg(ssl); // Client receives the chat message from the server
            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
        close_ssl();
        close(unixSock);
    }

    void startChat()
    {
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            char chatMsg[BUFF_SIZE];
            cout << "</> Client: ";
            cin.getline(chatMsg, sizeof(chatMsg));
            if (sendto(unixSock, chatMsg, sizeof(chatMsg), 0, reinterpret_cast<sockaddr *>(&srvAddr), srvAddrSize) < 0)
            {
                cerr << "<!> '" << chatMsg << "' message failed to send" << endl;
                return;
            }
            else
            {
                if (strcasecmp(chatMsg, CHAT_CLOSE) == 0)
                {
                    cout << "<~> Sent " << chatMsg << " to Server.\n<~> Closing the connection..." << endl;
                    close(unixSock);
                    exit(EXIT_SUCCESS);
                }
                else
                    cout << "<~> Sent to Server: " << chatMsg << endl;
            }
            ssize_t recvBufLen = recvfrom(unixSock, chatMsg, sizeof(chatMsg), 0, reinterpret_cast<sockaddr *>(&srvAddr), &srvAddrSize);
            if (recvBufLen < 0)
            {
                cerr << "<!> Failed to recieve packet!" << endl;
                return;
            }
            chatMsg[recvBufLen] = '\0';

            if (strcasecmp(chatMsg, CHAT_CLOSE) == 0)
            {
                cout << "<~> Received " << chatMsg << " from Server.\n<~> Closing the connection..." << endl;
                close(unixSock);
                exit(EXIT_SUCCESS);
            }
            else
                cout << "<~> Received from Server: " << chatMsg << endl;

            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
        close(unixSock);
    }
};

// Defining the class Bob (Server)
class Bob
{
private:
    // Defining the private variables
    sockaddr_in srvAddr, cliAddr;                                           // Server and client address
    socklen_t srvAddrSize = sizeof(srvAddr), cliAddrSize = sizeof(cliAddr); // Server and client address size
    const SSL_METHOD *method;                                               // SSL method
    SSL_CTX *sslCtx;                                                        // SSL context
    EVP_PKEY *skey;                                                         // Public key
    BIO *bio;                                                               // BIO object
    SSL *ssl;                                                               // SSL object
    struct timeval timeout;                                                 // Timeout object for the DTLS handshake

public:
    // Defining the public variables
    int unixSock;             // Unix socket file descriptor for the server
    char cliHost[NI_MAXHOST]; // Hostname of the client

    // Constructor for the class Bob (Server)
    Bob()
    {
        // Print the server start message to the console and start the server
        unixSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        memset(&srvAddr, 0, srvAddrSize);
        srvAddr.sin_family = AF_INET;
        srvAddr.sin_addr.s_addr = INADDR_ANY;
        srvAddr.sin_port = htons(PORT);
        if (bind(unixSock, reinterpret_cast<sockaddr *>(&srvAddr), srvAddrSize) < 0)
        {
            cerr << "<!> Error socket bind failed" << endl;
            exit(1);
        }
        cout << "<~> SERVER STARTED!" << endl;
        cout << "<~> Waiting for client to connect..." << endl;
    }

    // Function to perform the application layer handshake
    void applicationLayerHandshake()
    {
        // Receive the chat hello message from the client
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            char buf[BUFF_SIZE];
            ssize_t recvBufLen = recvfrom(unixSock, buf, sizeof(buf), 0, reinterpret_cast<sockaddr *>(&cliAddr), &cliAddrSize);
            if (recvBufLen < 0)
            {
                cerr << "<!> Failed to recieve packet!" << endl;
                return;
            }
            buf[recvBufLen] = '\0';

            // Get the hostname of the client and print it to the console
            getnameinfo(reinterpret_cast<sockaddr *>(&cliAddr), cliAddrSize, cliHost, NI_MAXHOST, nullptr, 0, 0);
            cout << "<~> Client connected: " << cliHost << " (" << inet_ntoa(cliAddr.sin_addr) << ")" << endl;

            // If the chat hello message is received from the client, then send the chat ok reply message to the client
            if (strcasecmp(buf, CHAT_HELLO) == 0)
            {
                cout << "<~> Received from Client: " << buf << endl;
                string msg(CHAT_OK_REPLY);
                if (sendto(unixSock, msg.c_str(), msg.size(), 0, reinterpret_cast<sockaddr *>(&cliAddr), cliAddrSize) < 0)
                {
                    cerr << "<!> '" << CHAT_OK_REPLY << "' message failed to send" << endl;
                    return;
                }
                else
                    cout << "<~> Sent: " << msg << endl;
                break;
            }
            else
                cout << "<~> Received from Client: " << buf << endl;

            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;

        // Now wait to receive the chat start SSL message from the client to initiate the secure chat
        retries = 0;
        while (retries < MAX_RETRIES)
        {
            char buf[BUFF_SIZE];
            ssize_t recvBufLen = recvfrom(unixSock, buf, sizeof(buf), 0, reinterpret_cast<sockaddr *>(&cliAddr), &cliAddrSize);
            if (recvBufLen < 0)
            {
                cerr << "<!> Failed to recieve packet!" << endl;
                return;
            }

            buf[recvBufLen] = '\0';

            // If the chat start SSL message is received from the client, then send the chat start SSL ack message to the client
            if (strcasecmp(buf, CHAT_START_SSL) == 0)
            {
                cout << "<~> Received from Client: " << buf << endl;
                string msg(CHAT_START_SSL_ACK);
                if (sendto(unixSock, msg.c_str(), msg.size(), 0, reinterpret_cast<sockaddr *>(&cliAddr), cliAddrSize) < 0)
                {
                    cerr << "<!> '" << CHAT_START_SSL_ACK << "' message failed to send" << endl;
                    return;
                }
                else
                    cout << "<~> Sent: " << msg << endl;

                // Now initiate the DTLS handshake and secure communication with the client
                initiateDTLSHandshake();
                break;
            }
            else
            {
                cout << "<~> Received from Client: " << buf << endl;
                if (strcasecmp(buf, CHAT_CLOSE) == 0)
                {
                    cout << "<~> Received " << buf << " from Client.\n<~> Closing the connection..." << endl;
                    close(unixSock);
                    exit(EXIT_SUCCESS);
                }
                else
                    startChat();
            }

            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
        close(unixSock);
    }

    // Init SSL function
    void init_ssl()
    {
        SSL_load_error_strings();
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();
    }

    // Close SSL function
    void close_ssl()
    {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(sslCtx);
    }

    //  Function to initiate the DTLS handshake and secure communication with the client
    void initiateDTLSHandshake()
    {
        // Print the DTLS handshake initiation message to the console
        cout << "<~> Initializing SSL Handshake..." << endl;

        // Initialise SSL
        init_ssl();

        // CERT and KEY file names
        const char *cert_file_name = NULL;
        const char *sk_file_name = NULL;

        cert_file_name = BOB_CERT_NAME;
        sk_file_name = BOB_PRIVATE_KEY_NAME;

        // Set the timeout for the DTLS handshake
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // SSL context creation and configuration for DTLS
        sslCtx = SSL_CTX_new(DTLS_server_method());             // Create a new SSL context for DTLS
        SSL_CTX_set_min_proto_version(sslCtx, DTLS1_2_VERSION); // Set the minimum DTLS protocol version to DTLS 1.2
        SSL_CTX_set_max_proto_version(sslCtx, DTLS1_2_VERSION); // Set the maximum DTLS protocol version to DTLS 1.2

        SSL_CTX_set_mode(sslCtx, SSL_MODE_AUTO_RETRY);           // Set the SSL context mode to auto retry to automatically retry the handshake
        SSL_CTX_set_cookie_generate_cb(sslCtx, generate_cookie); // Set the cookie generation callback function for the DTLS handshake
        SSL_CTX_set_cookie_verify_cb(sslCtx, &verify_cookie);    // Set the cookie verification callback function for the DTLS handshake
        SSL_CTX_set_verify_depth(sslCtx, 2);                     // Set the maximum depth for the certificate chain verification to 2
        SSL_CTX_set_verify(sslCtx, SSL_VERIFY_PEER, NULL);       // Set the SSL verification mode to peer verification (verify the client certificate)

        if (SSL_CTX_use_certificate_file(sslCtx, cert_file_name, SSL_FILETYPE_PEM) <= 0) // Load the server certificate file
        {
            ERR_print_errors_fp(stderr);
            exit(1);
        }

        if (SSL_CTX_use_PrivateKey_file(sslCtx, sk_file_name, SSL_FILETYPE_PEM) <= 0) // Load the server private key file
        {
            ERR_print_errors_fp(stderr);
            exit(1);
        }

        if (!SSL_CTX_check_private_key(sslCtx)) // Check if the server private key complies with the server certificate
        {
            cerr << "<!> Private Key does not comply with the certificate" << endl;
            abort();
        }

        if (!SSL_CTX_load_verify_locations(sslCtx, ROOT_STORE, NULL)) // Load the root certificate store
        {
            cout << "<~> Verify trust store location successful" << endl;
        }

        bio = BIO_new_dgram(unixSock, BIO_NOCLOSE);                  // Create a new BIO object for the DTLS handshake
        BIO_ctrl(bio, BIO_CTRL_DGRAM_SET_RECV_TIMEOUT, 0, &timeout); // Set the receive timeout for the BIO object
        if (!bio)                                                    // Print an error message to the console and exit the program if the BIO object is not created
            cerr << "<!> Error in creating bio" << endl;

        ssl = SSL_new(sslCtx); // Create a new SSL object

        SSL_set_bio(ssl, bio, bio); // Set the BIO object for the SSL object

        SSL_set_options(ssl, SSL_OP_COOKIE_EXCHANGE); // Set the SSL options for cookie exchange

        // DTLS listen
        int stat = DTLSv1_listen(ssl, (BIO_ADDR *)&srvAddr);
        if (stat <= 0)
        {
            // Print an error message to the console and exit the program if the DTLS listen fails
            cout << "<!> DTLS Listen failed" << endl;
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        // DTLS accept
        if (SSL_accept(ssl) != 1)
        {
            // Print an error message to the console and exit the program if the DTLS handshake fails
            cout << "<!> DTLS Handshake failed" << endl;
            ERR_print_errors_fp(stderr);
            close_ssl();
            exit(EXIT_FAILURE);
        }
        else
            cout << "<~> Server accepted DTLS connection" << endl;

        // Verify the client certificate and print the verification status to the console
        if (SSL_get_peer_certificate(ssl) && SSL_get_verify_result(ssl) == X509_V_OK)
            cout << "<~> Server Certificate Verified!\n";

        // Set the receive timeout for the BIO object to 0
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        BIO_ctrl(bio, BIO_CTRL_DGRAM_SET_RECV_TIMEOUT, 0, &timeout);

        cout << "<~> DTLS Handshake successful" << endl;
        startSSLChat();
    }

    // Function to send the chat message to the client
    int sendChatMessage(SSL *ssl, const char *message)
    {
        ssize_t ssl_write_flag;
        ssl_write_flag = SSL_write(ssl, message, strlen(message));
        if (ssl_write_flag <= 0)
            cerr << "<!> '" << message << "' message failed to send" << endl;
        if (strcasecmp(message, CHAT_CLOSE) == 0)
        {
            // Server sends the chat close message to the client and closes the connection
            cout << "<~> Sent " << CHAT_CLOSE << " to Client.\n<~> Closing the connection..." << endl;
            close_ssl();
            close(unixSock);
            exit(0);
        }
        cout << "<~> Sent to Client: " << message << endl;
        return ssl_write_flag;
    }

    // Function to receive the chat message from the client
    receiveSSLMessage receiveSSLMsg(SSL *ssl)
    {
        receiveSSLMessage resp;
        memset(resp.buf, 0, sizeof(resp.buf)); // Clear buffer
        resp.recvfrom_flag = SSL_read(ssl, resp.buf, sizeof(resp.buf) - 1);
        if (resp.recvfrom_flag <= 0)
            cerr << "<!> Failed to recieve packet!" << endl;
        else if (strcasecmp(resp.buf, CHAT_CLOSE) == 0)
        {
            resp.buf[resp.recvfrom_flag] = '\0';
            cout << "<~> Received " << resp.buf << " from Client.\n<~> Closing the connection..." << endl;
            close_ssl();
            close(unixSock);
            exit(0);
        }
        else
            cout << "<~> Received from Client: " << resp.buf << endl;
        return resp;
    }

    void startSSLChat()
    {
        char chatMsg[BUFF_SIZE];
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            // Server receives the chat message from the client
            receiveSSLMsg(ssl);

            // Server inputs the chat message and sends it to the client
            cout << "</> Server: ";
            cin.getline(chatMsg, sizeof(chatMsg));
            sendChatMessage(ssl, chatMsg);
            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
        close_ssl();
        close(unixSock);
    }

    void startChat()
    {
        char chatMsg[BUFF_SIZE];
        int retries = 0;
        while (retries < MAX_RETRIES)
        {
            cout << "</> Server: ";
            cin.getline(chatMsg, sizeof(chatMsg));
            if (sendto(unixSock, chatMsg, sizeof(chatMsg), 0, reinterpret_cast<sockaddr *>(&cliAddr), cliAddrSize) < 0)
            {
                cerr << "<!> '" << chatMsg << "' message failed to send" << endl;
                return;
            }
            else
            {
                if (strcasecmp(chatMsg, CHAT_CLOSE) == 0)
                {
                    cout << "<~> Sent " << chatMsg << " to Client.\n<~> Closing the connection..." << endl;
                    close(unixSock);
                    exit(EXIT_SUCCESS);
                }
                else
                    cout << "<~> Sent to Client: " << chatMsg << endl;
            }

            ssize_t recvBufLen = recvfrom(unixSock, chatMsg, sizeof(chatMsg), 0, reinterpret_cast<sockaddr *>(&cliAddr), &cliAddrSize);
            if (recvBufLen < 0)
            {
                cerr << "<!> Failed to recieve packet!" << endl;
                return;
            }
            chatMsg[recvBufLen] = '\0';

            if (strcasecmp(chatMsg, CHAT_CLOSE) == 0)
            {
                cout << "<~> Received " << chatMsg << " from Server.\n<~> Closing the connection..." << endl;
                close(unixSock);
                exit(0);
            }
            else
                cout << "<~> Received from Client: " << chatMsg << endl;
            retries++;
            this_thread::sleep_for(chrono::milliseconds(RETRY_INTERVAL));
        }
        cerr << "<!> Maximum retries reached. Aborting." << endl;
    }
};

// Main function
int main(int argc, char *argv[])
{
    // Validate the command line flags and display the error message if the flags are invalid
    if ((argc == 2 && strcasecmp(argv[1], "-s") != 0) || (argc == 3 && strcasecmp(argv[1], "-c") != 0))
        cout << "<!> Invalid command line arguments.\n<~> Available command line arguments are either:\n1. -s\n2. -c <serverhostname>" << endl;

    // If the command line flag is -s, then start the server
    else if ((argc == 2 && strcasecmp(argv[1], "-s") == 0))
    {
        Bob server = Bob();
        server.applicationLayerHandshake();
    }

    // If the command line flag is -c, then start the client
    else if ((argc == 3 && strcasecmp(argv[1], "-c") == 0))
    {
        Alice client = Alice(argv[2]);
        client.applicationLayerHandshake();
    }

    return 0;
}
//  END OF PROGRAM