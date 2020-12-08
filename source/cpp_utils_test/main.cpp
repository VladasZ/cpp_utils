
#include <memory>

#include "Log.hpp"
#include "LineID.hpp"

#define CU_CALL_COUNTER static constexpr auto id = CU_FUN_ID; id++; Log << id.call_count()

void cooo() {

    CU_CALL_COUNTER;

}

class ITest {
public:
    virtual std::string info() = 0;
};


class ATest : public ITest {
public:
    std::string info() override { return "A test"; }
};

class BTest : public ITest {
public:
    std::string info() override { return "B test"; }
};

class IntHolder {

    using Ptr = std::shared_ptr<ITest>;

private:

    Ptr ptr;

public:

    IntHolder() {
        ptr = std::shared_ptr<ITest>(new ATest);
    }

    Ptr value() {
        return ptr;
    }

};

int main() {

    IntHolder spes;

    //*spes.value() = BTest();

    new (spes.value().get()) BTest();

    Log << spes.value()->info();

    return 0;

}
