#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <netinet/in.h>
#include <sys/types.h>

#define DOMAIN AF_INET
#define Type SOCK_STREAM
#define PROTOCOL 0
#define PORT 7751

#define FLAG 0
#define BUFFER_SIZE 1024

using namespace std;
class Socket
{

public:
    /* adaptivesockfd  will be called on recv and send calls in TCP Class
     * and always hold the value of origin sock unless there's an accept called
     * on case of TCP Srever */
    int originsockfd, adaptivesockfd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    Socket(int type)
    {
        originsockfd = socket(DOMAIN, type, PROTOCOL);
        adaptivesockfd = originsockfd;
    }
    virtual ~Socket() {};

    virtual void connect() = 0;

    virtual void send(const std::string &message) = 0;

    virtual void receive() = 0;

    virtual void shutdown() = 0;

    void bind();
    virtual void listen();
    virtual int accept();
    virtual void configServertoMulticastSettings();
    virtual void joinMulticastGroup();
    virtual void reuse();
    virtual void leaveMulticastGroup();

    char buffer[BUFFER_SIZE];
};

#endif // SOCKET_HPP
