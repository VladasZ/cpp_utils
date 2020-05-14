
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

int rglica = 4;

int spesica = 10;


template <class ...Args>
void apply_rglica(std::function<void(Args& ...)> action, Args& ... args) {
    action(args ...);
}



int main() {

    apply_rglica([](int& rg, int& sp) {

    }, rglica, spesica);

//    System::execute(std::string() + "\"" + "/Applications/Sublime Text.app/Contents/SharedSupport/bin/subl" + "\"");



    return 0;

}
