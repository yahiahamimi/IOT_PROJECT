#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include "Socket.hpp"
#include <string>

class TCPSocket : public Socket
{
public:
    TCPSocket(int type) : Socket(type) {}
    void connect();

    void send(const std::string &message);

    void receive();

    void shutdown();

    void listen();
    int accept();
};

#endif // TCPSOCKET_HPP
