
#include <array>
#include <vector>

#include "Log.hpp"
#include "ArrayView.hpp"

using namespace cu;


int main() {

    static constexpr std::array<int, 7> ultro_galagol = { 1, 2, 3, 4, 5, 6, 7 };

    std::vector<int> spesogon = { 1, 2, 3, 4, 5 };

    for (auto i : spesogon) {
        Logvar(i);
    }

    Logvar(std::is_scalar_v<decltype(spesogon)>);

    ArrayView spiagron = spesogon;

    for (auto i : spiagron) {
        Logvar(i);
    }


    //ArrayView<int> kiko = ArrayView<int> { ultro_galagol };

    return 0;

}
