
#include "Log.hpp"
#include "LineID.hpp"

void cooo() {
    CU_LINE_ID++; Log << CU_LINE_ID.call_count();
}

int main() {

    constexpr auto id = CU_LINE_ID;

    CU_LINE_ID++; Log << CU_LINE_ID.call_count();

    Log << id.location(false);

    for (int i = 0; i < 20; i++) {
        cooo();
    }


    return 0;

}
