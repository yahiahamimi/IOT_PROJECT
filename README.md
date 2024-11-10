# Network Communication System

This project implements a network communication system that supports both unicast and multicast communication modes. It is designed to facilitate communication between a server and multiple clients using TCP and UDP protocols.

## Project Structure

The project is organized into several components:

- **Channel**: Abstract base class for different types of communication channels.
  - `ClientChannel`: Handles client-side communication.
  - `ServerChannel`: Handles server-side communication.

- **Socket**: Abstract base class for different types of sockets.
  - `TCPSocket`: Implements TCP-specific socket operations.
  - `UDPSocket`: Implements UDP-specific socket operations.

- **App**: Contains the main application logic for both server and client.
  - `Serverapp`: Server-side application logic.
  - `Clientapp`: Client-side application logic.

## Features

- **Unicast Communication**: Uses TCP sockets to establish a direct connection between a single client and server.
- **Multicast Communication**: Uses UDP sockets to allow a server to send messages to multiple clients in a multicast group.
- **Dynamic Connection Management**: Automatically handles connection setup and teardown based on the connection type.

## Usage

### Server

Compile and run the server application to start listening for client connections. The server can handle both unicast and multicast connections based on the configuration.

### Client

Compile and run the client application to connect to the server. The client can send and receive messages depending on the connection type.

## Configuration

- **CASTTYPE**: Define whether the communication is unicast or multicast.
  - `UNICAST`: Set for unicast communication.
  - `MULTICAST`: Set for multicast communication.

- **Network Settings**: Modify `PORT` and `MULTICAST_GROUP` in the socket configuration files for custom network settings.

## Dependencies

- C++ standard library
- System libraries for socket programming

## Build Instructions

Use a C++ compiler that supports C++11 or later. Ensure you have necessary permissions to use network sockets on your machine.

```bash
# Example build command using g++
g++ -o server src/server/Serverapp.cpp src/channel/*.cpp src/socket/*.cpp
g++ -o client src/client/Clientapp.cpp src/channel/*.cpp src/socket/*.cpp
```

## License

This project is open-source and available under the MIT License. 
