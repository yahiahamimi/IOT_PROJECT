#include "ClientChannel.hpp"

void ClientChannel ::start()
{
    if (ConnectionType == "UniCast")
    {
        channelSocket->connect();
    }

    else if (ConnectionType == "MultiCast")
    {
        /* enable reuse must happen before bind to allow 2 clients to bind a
         * reuseable socket to the same ipaddress and same port */
        channelSocket->reuse();
        channelSocket->bind();
        channelSocket->joinMulticastGroup();
    }
}

void ClientChannel::send(const string &message)
{
    if (ConnectionType == "UniCast")
    {
        cout << "Client: Sending Message: " << message << endl;

        channelSocket->send(message.c_str());
    }

    else if (ConnectionType == "MultiCast")
    {
        /* we assume that client is always receiving int the group in case of multicast udp */
    }
}

void ClientChannel::receive()
{

    cout << "Client: Receievd Message: ";
    channelSocket->receive();
}

void ClientChannel::stop()
{
    if (ConnectionType == "UniCast")
    {
        channelSocket->shutdown();

        close(channelSocket->originsockfd);
    }

    else if (ConnectionType == "MultiCast")
    {
        channelSocket->shutdown();
        channelSocket->leaveMulticastGroup();
        close(channelSocket->originsockfd);
    }
}