
#include <iostream>
#include <nuts_datagram.h>
#include <basic.h>
#include <chrono>
using std::cout, std::endl;

nuts_returns nuts_test_function(nuts_paramters &p) {
    if (p["test"].isNull()) {
        cout << "No" << endl;
        return "no";
    } else {
        cout << "ok" << endl;
        return "ok";
    }
}

int main() {

}