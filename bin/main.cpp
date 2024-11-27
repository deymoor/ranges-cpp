#include <iostream>
#include <vector>
#include <libs/ranges.h>

int main() {
    std::vector<int> a = {1, 2, 3};
    // auto not_even = [](int i) {return i % 2 == 0;};
    for (auto i : a | ranges::take(2)) {
        std::cout << i << ' ';
    }
}