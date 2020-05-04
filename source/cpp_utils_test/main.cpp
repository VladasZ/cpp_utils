
#include <vector>

#include "Log.hpp"
#include "ArrayView.hpp"

using namespace cu;


int main() {

    std::vector<int> spesogon = { 1, 2, 3, 4, 5 };

    for (auto i : spesogon) {
        Logvar(i);
    }

    Logvar(std::is_scalar_v<decltype(spesogon)>);

    ArrayView spiagron = spesogon;

    for (auto i : spiagron) {
        Logvar(i);
    }


    return 0;

}
