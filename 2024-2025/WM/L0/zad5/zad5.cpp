#include <iostream>
#include <functional>

int main() {
    auto f = [](int x) { return 1 + x * (x + 1); };
    auto g = [](int x, int y) { return x + y * y; };
    auto h = [](int y, int x) { return x + y * y; };

    std::cout << f(2) << " " << g(2, 3) << " " << h(3, 2) << std::endl;
}

