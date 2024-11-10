#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"
#include <string>

using namespace std;
#define MULTICAST_GROUP "239.0.0.1"
#define PORT 7751

class Channel
{
private:
protected:
    string ConnectionType;
    Socket *channelSocket;

public:
    Channel(string ConnectionType) : ConnectionType(ConnectionType)
    {
        if (ConnectionType == "UniCast")
            channelSocket = new TCPSocket(SOCK_STREAM);
        else if (ConnectionType == "MultiCast")
            channelSocket = new UDPSocket(SOCK_DGRAM);
        else
        {
        }
    }

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void send(const std::string &message) = 0;

    virtual void receive() = 0;
};
#endif // CHANNEL_HPP
