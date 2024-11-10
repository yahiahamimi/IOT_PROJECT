#include "TCPSocket.hpp"

void TCPSocket::connect()
{
    address.sin_family = DOMAIN;
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        std::cerr << "Invalid address!" << std::endl;
    }
    address.sin_port = htons(PORT);

    // address structure that specifies the address (IP address and port) of the server to connect to.
    if (::connect(originsockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        cout << "connect function failed. Error code: " << errno << " (" << strerror(errno) << ")" << endl;
        close(originsockfd);
        exit(1);
    }
    else
    {
        cout << "Client:client connected to a server its IPaddress 127.0.0.1 and its port: " << PORT << endl;
    }
}

void TCPSocket::send(const std::string &message)
{

    // std::cout << "Message to send: " << message << std::endl; // Should print "Hello, Client!"

    // for (int i = 0; i < message.size(); i++)
    // {
    //     std::cout << "message[" << i << "]: " << (int)message[i] << std::endl;
    // }

    // std::cout << "Address of message: " << message.size() << std::endl;

    // std::cout << "Message length (strlen): " << strlen(message.c_str()) << std::endl; // Should print 15

    // // Additionally, check the size of the message array
    // std::cout << "sizeof(message): " << message.size() << std::endl; // Should print the size of the pointer, not the string length

    // // Send the message
    ssize_t sent = ::send(adaptivesockfd, message.c_str(), message.size(), 0);
    // std::cout << "Sent " << sent << " bytes successfully." << std::endl;

    if (sent < 0)
    {
        std::cerr << "Send failed: " << strerror(errno) << std::endl;
    }
}

void TCPSocket::receive()
{

    // cout << "currently recieveing" << endl;

    int received_value = ::recv(adaptivesockfd, buffer, BUFFER_SIZE, 0);

    if (received_value == 0)
    {
        std::cout << "Connection closed by peer." << std::endl;
        close(originsockfd);
    }
    else if (received_value < 0)
    {
        // Check specific error codes
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            cout << "recv would block; try again later." << endl;
        }
        else
        {
            cerr << "recv error: " << strerror(errno) << endl;
            close(originsockfd);
        }
    }
    else
    {
        // // Display data in hexadecimal format for debugging
        // std::cout << "Received " << received_value << " bytes (hex): ";
        // for (ssize_t i = 0; i < received_value; ++i)
        // {
        //     std::cout << std::hex << std::setw(2) << std::setfill('0')
        //               << (static_cast<unsigned int>(buffer[i]) & 0xFF) << " ";
        // }
        // std::cout << std::endl;
        // // Null-terminate if we received fewer than BUFFER_SIZE bytes
        // if (received_value < BUFFER_SIZE)
        // {
        //     buffer[received_value] = '\0';
        // }
        // else
        // {
        //     buffer[BUFFER_SIZE - 1] = '\0';
        // }

        // Successfully received data
        // cout << "Received " << (int)received_value << " bytes: " << string(buffer, received_value) << endl;

        // for (ssize_t i = 0; i < received_value; ++i)
        // {
        //     std::cout << buffer[i]; // Display each byte
        // }
        // std::cout << std::endl;

        cout << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }
}

void TCPSocket::shutdown()
{
    ::shutdown(originsockfd, SHUT_RDWR);
}

void TCPSocket::listen()
{
    if (::listen(originsockfd, 1) < 0)
    {
        cout << "listening operation failed. Error code: " << errno << " (" << strerror(errno) << ")" << endl;
        close(originsockfd);
        exit(1);
    }
    else
    {
        cout << "server is listening to on original socket with fd: " << originsockfd << endl;
    }
}
int TCPSocket::accept()
{
    struct sockaddr_in client_addr;
    int clientlen = sizeof(client_addr);
    // when accept is done it fills the passed address structue by the client info and ip
    adaptivesockfd = ::accept(originsockfd, (struct sockaddr *)&client_addr, (socklen_t *)&clientlen);
    if (adaptivesockfd < 0)
    {
        std::cerr << "Accepting operation failed. Error code: " << errno << " (" << strerror(errno) << ")\n";
        close(originsockfd);
        exit(1);
    }
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(client_addr.sin_port);

    cout << "Server: Client connected from IP: " << client_ip << " Port: " << client_port << "with file descriptor: " << adaptivesockfd << endl;
}