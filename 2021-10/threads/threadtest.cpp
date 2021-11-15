#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using milliseconds = std::chrono::milliseconds;
using steady_clock = std::chrono::steady_clock;

static auto start = steady_clock::now();
static std::mutex mutex;  // used to ensure std::cout is uninterrupted

long long ms_from_start() {
    return std::chrono::duration_cast<milliseconds>(steady_clock::now() - start).count();
}

void thread_action(std::string name, int ms) {
    mutex.lock();
    std::cout << name << " started at " << ms_from_start() << "ms" << std::endl;
    mutex.unlock();

    std::this_thread::sleep_for(milliseconds(ms));

    mutex.lock();
    std::cout << name << " finished at " << ms_from_start() << "ms" << std::endl;
    mutex.unlock();
}

int main() {
    std::thread t1(thread_action, "t1", 250);
    std::thread t2(thread_action, "t2", 500);
    t1.join();
    std::thread t3(thread_action, "t3", 750);
    t2.join();
    t3.join();
}
