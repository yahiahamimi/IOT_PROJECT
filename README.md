IoT Communication System Using Sockets
Overview
This project implements an IoT device communication system in C++ using TCP and UDP sockets to establish connections between multiple client devices (emulated using QEMU) and a central server on a Raspberry Pi 4. The communication process is encapsulated within an object-oriented structure, ensuring modularity and scalability for unicast (TCP) and multicast (UDP) communications.

The project demonstrates the use of object-oriented programming (OOP) principles such as inheritance, polymorphism, and encapsulation. It is designed for real-time sensor data exchange between IoT devices, built using Yocto for Raspberry Pi 4 and QEMU for emulating the client environment.

Project Goals
Establish TCP-based unicast communication for one-to-one data exchange.
Implement UDP-based multicast communication to broadcast messages to multiple clients.
Utilize an object-oriented approach to encapsulate the socket communication.
Cross-compile the project for Raspberry Pi 4 using Yocto and automate the build process with Makefile.
Project Structure
The project contains organized modules, each handling specific responsibilities, including socket management, client-server communication, and data handling.

Directory Layout
plaintext
Copy code
/iot_project
│
├── src
│   ├── socket
│   │   ├── Socket.hpp
│   │   ├── Socket.cpp
│   │   ├── TCPSocket.hpp
│   │   ├── TCPSocket.cpp
│   │   ├── UDPSocket.hpp
│   │   └── UDPSocket.cpp
│   ├── channel
│   │   ├── Channel.hpp
│   │   ├── ServerChannel.hpp
│   │   ├── ServerChannel.cpp
│   │   ├── ClientChannel.hpp
│   │   └── ClientChannel.cpp
│   ├── client
│   │   ├── ClientApp.hpp
│   │   └── ClientApp.cpp
│   └── server
│       ├── ServerApp.hpp
│       └── ServerApp.cpp
├── include
├── Makefile
└── README.md
Key Components
1. Abstract Socket Class
The Socket abstract class provides the foundational behavior for both TCP and UDP communication by defining essential socket operations as pure virtual functions.

cpp
Copy code
// Socket.hpp
virtual void connect() = 0;
virtual void send(const std::string& message) = 0;
virtual void receive() = 0;
virtual void shutdown() = 0;
2. Derived Socket Classes (TCPSocket and UDPSocket)
TCPSocket: Implements the methods specific to TCP communication, such as establishing a one-to-one connection with the server and handling message exchange.
UDPSocket: Implements the methods specific to UDP communication, designed for multicasting messages to multiple clients.
These classes inherit from Socket and override its virtual methods, ensuring protocol-specific functionality.

3. Abstract Channel Class
The Channel class abstracts the client-server communication channel. It contains a Socket* pointer (channelSocket) which can point to either a TCPSocket or UDPSocket object, depending on the application needs.

cpp
Copy code
// Channel.hpp
Socket* channelSocket;
virtual void start() = 0;
virtual void stop() = 0;
virtual void send(const std::string& message) = 0;
virtual void receive() = 0;
4. ServerChannel and ClientChannel Classes
These classes derive from Channel and implement specific behaviors for server and client roles:

ServerChannel: Manages server-specific functionalities like accepting client connections (TCP) and broadcasting updates (UDP).
ClientChannel: Manages client functionalities such as connecting to the server and receiving messages.
5. Application Classes (ClientApp and ServerApp)
The ClientApp and ServerApp classes encapsulate the main application logic, handling the flow of actions for each side of the communication:

ServerApp: Initializes the server, listens for connections (TCP), or sends periodic updates (UDP).
ClientApp: Connects to the server, sends messages, and listens for responses.
Workflow
Unicast TCP Communication
ServerApp (Raspberry Pi 4):

The server listens on a specified port.
Upon a client's connection, the server sends an acknowledgment along with a simulated temperature reading.
ClientApp (QEMU):

The client connects to the server, sends a message, and waits for the server’s response.
Example Server Output:

arduino
Copy code
Server: Client connected from IP: [X.X.X.X].
Server: Received message: [Hello, Server!]
Server: Sending acknowledgment. Current Temperature is 39°C
Example Client Output:

arduino
Copy code
Client: Connected to Server.
Client: Sending message: [Hello, Server!]
Client: Received acknowledgment: [Message received.]
Multicast UDP Communication
ServerApp:

Sets up a multicast UDP socket.
Broadcasts messages to multiple clients periodically, simulating system updates or alerts.
ClientApp:

Listens on a multicast address for updates and displays each received message.
Example Server Output:

sql
Copy code
Server: Sending multicast message: [System update at 10:00 AM].
Example Client Output:

sql
Copy code
Client 1: Received multicast message: [System update at 10:00 AM].
Client 2: Received multicast message: [System update at 10:00 AM].
Development Environment
Yocto Setup
Configure Yocto to cross-compile the application for the Raspberry Pi 4.
Set up Yocto recipes for building and deploying server and client applications.
Deploy Yocto-generated images onto the Raspberry Pi 4 for server testing.
QEMU Setup
QEMU emulates the client devices for testing both unicast (TCP) and multicast (UDP) applications on a PC.

Makefile Automation
A well-structured Makefile facilitates compiling both the server and client applications. You can build them independently using:

bash
Copy code
make -f Makefile.server    # Builds the server application
make -f Makefile.client    # Builds the client application
Usage Instructions
Build the Server Application:
bash
Copy code
make -f Makefile.server
Run the Server:
bash
Copy code
./bin/server
Build the Client Application:
bash
Copy code
make -f Makefile.client
Run the Client:
bash
Copy code
./bin/client
Key Technologies
C++ OOP: Modular design with inheritance, polymorphism, and encapsulation.
STL Containers: std::vector, std::queue, and std::string are used for efficient data management.
Yocto: Cross-compiles the application for Raspberry Pi.
QEMU: Emulates client communication.
Conclusion
This project provides a robust foundation for IoT device communication using sockets, leveraging object-oriented design and cross-platform compatibility. The clear separation between TCP and UDP handling ensures that the system can be easily extended to support additional protocols or enhanced functionality.


