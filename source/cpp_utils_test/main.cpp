

#include "Log.hpp"
#include "RangeConversion.hpp"

using namespace cu;

int main() {

    RangeConversion conv { 2, 3, 10, 110 };

    conv.flip = true;

    for (float i = 2; i < 3; i += 0.01) {
        conv = i;
        Log((float)conv);
    }

    return 0;

}
