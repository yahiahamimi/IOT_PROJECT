

#include "Serverapp.hpp"

using namespace std;

int main()
{
#if (CASTTYPE == UNICAST)
    ServerChannel s1("UniCast");

    cout << ".............Server is created..........." << endl;

    s1.start();
    cout << "................server started................" << endl;
    s1.receive();
    s1.send("Hello, Client I,m server s1 after u reapet with ack i'll send you the time");
    s1.receive();
    std::string currentDateTime = getCurrentDateTime();
    s1.send(currentDateTime);
    s1.stop();

#endif

    /*-----------------------------------------------------------------------------------------------*/
#if (CASTTYPE == MULTICAST)
    std::string currentDateTime;
    ServerChannel s2("MultiCast");
    s2.start();
    cout << "................server started................" << endl;
    while (1)
    {
        currentDateTime = getCurrentDateTime();
        sleep(2);
        s2.send(currentDateTime);
    }
    // s2.stop();
#endif
}

std::string getCurrentDateTime()
{
    // Get current time as a time_point object
    auto now = std::chrono::system_clock::now();

    // Convert to time_t (epoch time)
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to string using ctime (ctime adds a newline at the end)
    std::string currentTime = std::ctime(&now_time_t);

    // Remove newline character
    currentTime.pop_back();

    return currentTime;
}