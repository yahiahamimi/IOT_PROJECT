#include "ServerChannel.hpp"

int newfiledescriptor;

void ServerChannel::start()
{
    if (ConnectionType == "UniCast")
    {
        channelSocket->bind();
        channelSocket->listen();
        newfiledescriptor = channelSocket->accept();
    }

    else if (ConnectionType == "MultiCast")
    {
        channelSocket->reuse();
        channelSocket->configServertoMulticastSettings();
    }
}

void ServerChannel::stop()
{
    if (ConnectionType == "UniCast")
    {
        channelSocket->shutdown();
        close(newfiledescriptor);
        close(channelSocket->originsockfd);
    }

    else if (ConnectionType == "MultiCast")
    {
        channelSocket->shutdown();
        close(channelSocket->originsockfd);
    }
}

void ServerChannel::send(const std::string &message)
{
    /* The key here is the usage of const std::string&. Since you're passing the string as const std::string& message,
     * the function receives a reference to the string, and the original string is not copied.
     * This is perfectly fine, but when you print sizeof(message), you're printing the size of the reference,
     * not the actual string data.If you pass a std::string (like "Hello, Client!") to the send() method,
     * you're passing a reference to the string object itself, which includes the internal metadata (such as capacity and length).
     * However, the actual data (i.e., the message) is stored separately in memory. */

    cout << "Server: Sending Message: " << message << endl;
    channelSocket->send(message.c_str());
}

void ServerChannel::receive()
{
    if (ConnectionType == "UniCast")
    {
        cout << "Server: Receievd Message: ";
        channelSocket->receive();
    }

    else if (ConnectionType == "MultiCast")
    {
        /* We assume the server is always sending to the multigroup in cas of udp multicast */
    }
}
