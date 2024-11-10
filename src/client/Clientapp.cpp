
#include "clientapp.hpp"

using namespace std;

int main()
{
#if (CASTTYPE == UNICAST)
    ClientChannel c1("UniCast");
    cout << ".............Client is created..........." << endl;

    c1.start();
    cout << ".............Client is started..........." << endl;

    c1.send("Hi, I,m client c1 I want to ask about time");
    c1.receive();

    c1.send("ack");
    c1.receive();

    c1.stop();
#endif
/*-------------------------------------------------------------------------*/
#if (CASTTYPE == MULTICAST)
    ClientChannel c2("MultiCast");
    cout << ".............Client is created..........." << endl;
    c2.start();
    cout << ".............Client is started..........." << endl;
    while (1)
    {
        c2.receive();
    }
#endif
    // for (int i = 0; i < 10; i++)
    // {
    //     c2.receive();
    // }
    // c2.stop();
    // cout << "test done " << endl;

    // c2.receive();

    // cout << ".............Client is started..........." << endl;
    // // while (1)
    // // {
    // //     c2.receive();
    // // }
    // for (int i = 0; i < 10; i++)
    // {
    //     c2.receive();
    // }
    // c2.stop();
}