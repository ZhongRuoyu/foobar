#include <iostream>
#include <utility>

template <typename List>
struct LogData {
    using Type = List;
    List list;
};

struct None {};

template <typename Begin, typename Value>
LogData<std::pair<Begin &&, Value &&>> operator<<(LogData<Begin> &&begin,
                                                  Value &&value) noexcept {
    return {{std::forward<Begin>(begin.list), std::forward<Value>(value)}};
}

template <typename TLogData>
void Log(const char *file, int line, TLogData &&data) noexcept
    __attribute__((__noinline__)) {
    std::cerr << file << "(" << line << "): ";
    LogRecursive(std::cerr, std::forward<typename TLogData::Type>(data.list));
    std::cerr << std::endl;
}

template <typename TLogDataPair>
void LogRecursive(std::ostream &os, TLogDataPair &&data) noexcept {
    LogRecursive(os,
                 std::forward<typename TLogDataPair::first_type>(data.first));
    os << std::forward<typename TLogDataPair::second_type>(data.second);
}

inline void LogRecursive(std::ostream &os, None) noexcept {}

using PfnManipulator = std::ostream &(*)(std::ostream &);

template <typename Begin>
LogData<std::pair<Begin &&, PfnManipulator>> operator<<(
    LogData<Begin> &&begin, PfnManipulator pfn) noexcept {
    return {{std::forward<Begin>(begin.list), pfn}};
}

template <typename Begin, size_t n>
LogData<std::pair<Begin &&, const char *>> operator<<(
    LogData<Begin> &&begin, const char (&sz)[n]) noexcept {
    return {{std::forward<Begin>(begin.list), sz}};
}

#define LOG(msg) \
    if (true) Log(__FILE__, __LINE__, LogData<None>() << msg)

int main() {
    LOG(11111 << 22222 << 33333);
    return 0;
}
