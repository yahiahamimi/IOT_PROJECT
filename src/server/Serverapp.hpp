#ifndef SERVERAPP_HPP
#define SERVERAPP_HPP

#include "ServerChannel.hpp"

#include <string>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <ctime>

#define UNICAST 0
#define MULTICAST 1

#define CASTTYPE MULTICAST

std::string getCurrentDateTime();

#endif // SERVERAPP_HPP
