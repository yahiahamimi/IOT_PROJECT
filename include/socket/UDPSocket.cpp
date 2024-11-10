#include "UDPSocket.hpp"

void UDPSocket::connect()
{
    /* udp is connectionless */
}

void UDPSocket::send(const std::string &message)
{

    ssize_t sent = ::sendto(originsockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&servaddr, saddrlen);

    if (sent < 0)
    {
        std::cerr << "Send failed: " << strerror(errno) << std::endl;
    }
}

void UDPSocket::receive()
{
    int received_value = ::recvfrom(originsockfd, buffer, BUFFER_SIZE, 0, nullptr, nullptr);

    if (received_value == -1)
    {
        std::cerr << "Receive failed: " << strerror(errno) << std::endl;
        close(originsockfd);
    }
    else if (received_value == 0)
    {

        // Connection closed (unlikely with UDP, but can indicate an empty message)
        cout << "Received an empty message." << endl;
    }
    else
    {
        cout << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }
}
void UDPSocket::shutdown()
{
    // leave multicast group
    // setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    ::shutdown(originsockfd, SHUT_RDWR);
}

void UDPSocket::reuse()
{
    /* reuse m allow 2 clients to bind a reuseable socket to the same ipaddress
     * and same port very useful in case we have all clients on same machine
     */
    int reuseOptVal = TRUE;

    if (setsockopt(originsockfd, SOL_SOCKET, SO_REUSEADDR, &reuseOptVal, sizeof(reuseOptVal)) == -1)
    {
        std::cerr << "Failed to set SO_REUSEADDR: " << strerror(errno) << std::endl;
        close(originsockfd);
        exit(1);
    }
    else
    {
        std::cout << "SO_REUSEADDR set successfully on UDP socket." << std::endl;
    }
}

void UDPSocket::configServertoMulticastSettings()
{

    // Configure the server address for the multicast group
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    servaddr.sin_port = htons(PORT);

    // Set TTL (Time to Live) for the multicast packet
    unsigned char ttl = 1;
    if (setsockopt(originsockfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0)
    {
        std::cerr << "Failed to set TTL" << strerror(errno) << endl;
        close(originsockfd);
        exit(1);
    }
    else
    {

        std::cout << "Multicast server is ready to send to group " << MULTICAST_GROUP << std::endl;
    }
}

void UDPSocket::joinMulticastGroup()
{

    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(originsockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        cerr << "Failed to join multicast group" << strerror(errno) << endl;
        close(originsockfd);
    }

    cout << "A client has joined multicast group: " << MULTICAST_GROUP << endl;
}

void UDPSocket::leaveMulticastGroup()
{
    // leave multicast group
    setsockopt(originsockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    cout << "A client has leaved multicast group: " << MULTICAST_GROUP << endl;
}