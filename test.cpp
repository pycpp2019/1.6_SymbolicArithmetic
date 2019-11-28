#include <memory>

int main() {
    auto u = std::make_unique<int>(10);
    return 0;
}