
#include "Log.hpp"
#include "LineID.hpp"

#define CU_CALL_COUNTER static constexpr auto id = CU_FUN_ID; id++; Log << id.call_count()

void cooo() {

    CU_CALL_COUNTER;

}

int main() {

    for (int i = 0; i < 20; i++) {
        cooo();
    }


    return 0;

}
