
#include <tuple>
#include <array>

#include "Log.hpp"
#include "ArrayUtils.hpp"

constexpr std::array<int, 5> arr = { 1, 2, 3, 4, 10 };
static_assert(cu::array::static_exists<arr>(10));


constexpr std::array<std::string_view, 2> st_array = { "lo", "ko" };

static_assert(cu::array::static_exists<st_array>("ko"));

static_assert(st_array[1] == "ko");

int main() {


    //static_assert(only_int(tup));
}
