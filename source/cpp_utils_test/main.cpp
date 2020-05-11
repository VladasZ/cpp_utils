
#include <map>
#include <cassert>


#include "App.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "DataUtils.hpp"
#include "ArrayUtils.hpp"
#include "CircularBuffer.hpp"

using namespace cu;
using namespace std;

void print(int a) {
    cout << a << endl;
}

int main() {

    CircularBuffer<7> buf;

    std::array<uint8_t, 5> dote = { 1, 2, 3, 4, 5 };


    Logvar(dote);
    push_byte(dote, 10);
    Logvar(dote);


    System::execute(std::string() + "\"" + "/Applications/Sublime Text.app/Contents/SharedSupport/bin/subl" + "\"");

    return 0;

    std::array<uint8_t, 5> rodoko;


    for (int i = 0; i < 20000; i++) {
        buf.add(dote);
        //Log(buf.dump());
        buf.get(rodoko);
        //Logvar(cu::array::to_string(rodoko));
        assert(dote == rodoko);

    }


    Log("spes");


    std::map<int, int> doo;

    doo[5] = 6;

    int& spes = doo[5];

    Logvar(doo[5]);
    Logvar(spes);
    doo[5] = 422314324;
    Logvar(spes);


    return 0;

}
