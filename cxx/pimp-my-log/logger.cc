#include <cstddef>
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

// NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
template <typename Begin, std::size_t N>
LogData<std::pair<Begin &&, const char *>> operator<<(
    LogData<Begin> &&begin, const char (&str)[N]) noexcept {
  return {{std::forward<Begin>(begin.list), str}};
}
// NOLINTEND(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)

template <typename Begin>
LogData<std::pair<Begin &&, std::ostream &(*)(std::ostream &)>> operator<<(
    LogData<Begin> &&begin, std::ostream &(*func)(std::ostream &)) noexcept {
  return {{std::forward<Begin>(begin.list), func}};
}

inline void LogRecursive(std::ostream & /* unused */,
                         None /*unused*/) noexcept {}

template <typename LogDataPair>
void LogRecursive(std::ostream &ostream, LogDataPair &&data) noexcept {
  LogRecursive(ostream,
               std::forward<typename LogDataPair::first_type>(data.first));
  ostream << std::forward<typename LogDataPair::second_type>(data.second);
}

struct Logger {
  Logger(const char *file, int line, const char *severity) noexcept
      : file(file), line(line), severity(severity) {}

  template <typename LogData>
  void __attribute__((__noinline__)) operator<<=(LogData && data) noexcept {
    std::cerr << "" << severity << " " << file << ":" << line << " ";
    LogRecursive(std::cerr, std::forward<typename LogData::Type>(data.list));
    std::cerr << "\n";
  }

  const char *file;
  int line;
  const char *severity;
};

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#define LOG(severity)                                          \
  static_assert(#severity[0] != '\0', "severity must be set"); \
  if (true) Logger(__FILE__, __LINE__, #severity) <<= LogData<None>()

#define INFO() LOG(I)
#define WARNING() LOG(W)
#define ERROR() LOG(E)

// NOLINTEND(cppcoreguidelines-macro-usage)

int Log() {
  std::string file = "blah.txt";
  int error = 123;
  INFO() << "Read failed: " << file << " (" << error << ")";
  return 0;
}

int main() { Log(); }
