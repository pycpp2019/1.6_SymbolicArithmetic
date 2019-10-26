#include <iostream>
#include <sstream>

#include <vector>
#include <string>
#include <stack>
#include <functional>
#include <utility>

#include "rng.hh"

#include <Common.h>


static const int ATTEMPTS = 16;

int main() {
    std::vector<std::pair<std::string, std::function<bool(Rng*)>>> tests = {
        std::make_pair("Value", [](Rng *rng) -> bool {
            std::cout << Value(10)->ToString() << std::endl;
            return false;
        }),
    };

    Rng rng(0xDEADBEEF);

    int total = tests.size();
    int failed = 0;
    int counter = 0;

    for (std::pair<std::string, std::function<bool(Rng*)>> &pair : tests) {
        std::cout << "(" << counter << "/" << total << ") ";
        std::cout << pair.first << " ... " << std::flush;

        bool ok;
        try {
            ok = pair.second(&rng);
        } catch (...) {
            ok = false;
            std::cout << "unexpected exception caught" << std::endl;
        }

        if (ok) {
            std::cout << "ok";
        } else {
            failed += 1;
            std::cout << "fail";
        }
        std::cout << std::endl;
        counter += 1;
    }

    int ret = 0;
    std::cout << "result: ";
    if (failed > 0) {
        std::cout << "fail";
        ret = 1;
    } else {
        std::cout << "ok";
    }
    std::cout << ". " << total - failed << " passed, " << failed << " failed." << std::endl;

    return ret;
}
