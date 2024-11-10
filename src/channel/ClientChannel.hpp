#ifndef CLIENTCHANNEL_HPP
#define CLIENTCHANNEL_HPP

#include "Channel.hpp"
#include <string>
using namespace std;

class ClientChannel : public Channel
{

public:
    ClientChannel(string ConnectionType) : Channel(ConnectionType) {}

    void start();
    void send(const string &message);
    void receive();
    void stop();
};

#endif // CLIENTCHANNEL_HPP