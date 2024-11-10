#include "Socket.hpp"

void Socket::bind()
{

    address.sin_family = DOMAIN;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); // Bind to port 8080
    if (::bind(originsockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed. Error code: " << errno << " (" << strerror(errno) << ")\n";
        close(originsockfd);
    }
    else
    {

        cout << "binded succefully to (ANY_ADDRESS) and port: " << PORT << endl;
    }
}

void Socket ::joinMulticastGroup() {}
void Socket ::reuse() {}
void Socket ::leaveMulticastGroup() {}
void Socket ::listen() {}
void Socket ::configServertoMulticastSettings() {}
int Socket ::accept() {}