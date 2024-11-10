#ifndef SERVERCHANNEL_HPP
#define SERVERCHANNEL_HPP

#include "Channel.hpp"
#include <string>

class ServerChannel : public Channel
{

private:
    struct sockaddr_in cliaddr;

public:
    ServerChannel(string ConnectionType) : Channel(ConnectionType) {}

    void start();

    void send(const string &message);

    void receive();

    void stop();
};

#endif // SERVERCHANNEL_HPP
