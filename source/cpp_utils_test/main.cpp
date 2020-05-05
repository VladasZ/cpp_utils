
#include "Log.hpp"
#include "ArrayUtils.hpp"
#include "CircularBuffer.hpp"

using namespace cu;


int main() {

    CircularBuffer<7> buf;

    std::array<uint8_t, 5> dote = { 1, 2, 3, 4, 5 };

    std::array<uint8_t, 5> rodoko;



    for (int i = 0; i < 200000000; i++) {
        buf.add(dote);
        //Log(buf.dump());
        buf.get(rodoko);
        //Logvar(cu::array::to_string(rodoko));
        assert(dote == rodoko);

    }


    Log("spes");


    return 0;

}
