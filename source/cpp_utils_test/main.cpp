
#include "Log.hpp"
#include "Event.hpp"

using namespace cu;
using namespace std;


Event<> on_call;

Event<int> on_int;


int main() {

    on_int = [](auto value) {
        Logvar(value);
    };

    int some_int = 10;

    Log("Hello");


    on_int = some_int;

    Logvar(some_int);
    on_int(500);
    Logvar(some_int);

    cout << "A" << "B" << endl;

    return 0;
}
