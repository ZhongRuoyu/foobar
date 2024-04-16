#include <atomic>
#include <iostream>
#include <string>

#include "concurrent.h"

int x(0);
std::atomic<int> y(0);

std::mutex mutex;

void thread_action(unsigned int n) {
    for (unsigned i = 0; i < n; ++i) {
        ++x;
        ++y;
    }
}

int main() {
    concurrent<void, unsigned int> pool(3, thread_action, 2'000'000);
    pool.run();
    // std::cout << "x = " << x << "; y = " << y << std::endl;
    pool.join();
    std::cout << "x = " << x << "; y = " << y << std::endl;
}
