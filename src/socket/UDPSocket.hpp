#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP

#include "Socket.hpp"
#include <string>

using namespace std;
#define MAXMIMUM_CONNECTIONS 2
#define MULTICAST_GROUP "239.0.0.1"
#define TRUE 1
class UDPSocket : public Socket
{

public:
    UDPSocket(int type) : Socket(type) {}
    void connect();
    void send(const std::string &message);
    void receive();
    void shutdown();
    void reuse();
    void configServertoMulticastSettings();
    void joinMulticastGroup();
    void leaveMulticastGroup();

    struct ip_mreq mreq;

    struct sockaddr_in servaddr;
    int saddrlen = sizeof(servaddr);
};

#endif // UDPSOCKET_HPP
