#ifndef CONCURRENT_H_
#define CONCURRENT_H_

#include <functional>
#include <thread>
#include <tuple>
#include <vector>

template <class R, class... Args>
class concurrent {
    const unsigned int num_threads;
    const std::function<R(Args...)> f;
    const std::tuple<Args...> args;
    std::vector<std::thread> threads;
    bool started = false;
    bool joined = false;

   public:
    concurrent() = delete;

    concurrent(const concurrent<R, Args...> &pool) = delete;

    explicit concurrent(const std::function<R(Args...)> &&f,
                        const Args &&...args)
        : concurrent(std::thread::hardware_concurrency(), f,
                     std::make_tuple(args...)) {}

    explicit concurrent(const unsigned int num_threads,
                        const std::function<R(Args...)> &&f,
                        const Args &&...args)
        : num_threads(num_threads), f(f), args(std::make_tuple(args...)) {}

    ~concurrent() {
        if (!joined) {
            join();
        }
    }

    unsigned threads_count() { return num_threads; }

    void run() {
        if (!started) {
            started = true;
            for (unsigned int i = 0; i < num_threads; ++i) {
                threads.push_back(std::make_from_tuple<std::thread>(
                    std::tuple_cat(std::make_tuple(f), args)));
            }
        }
    }

    void join() {
        if (started) {
            for (auto &thread : threads) {
                thread.join();
            }
            joined = true;
        }
    }
};

#endif /* CONCURRENT_H_ */
