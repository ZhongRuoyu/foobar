#include <iostream>
#include <string>
#include <utility>

#include "cache_proxy.h"

int Add(int lhs, int rhs) {
  std::cout << "Add(" << lhs << ", " << rhs << ") invoked" << std::endl;
  return lhs + rhs;
}

std::string::size_type Strlen(const std::string &str) {
  std::cout << "Strlen(" << str << ") invoked" << std::endl;
  return str.length();
}

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
int main() {
  Proxy add_proxy(Add);
  auto proxied_add = [&](auto lhs, auto rhs) {
    auto result = add_proxy(lhs, rhs);
    std::cout << "proxied_add(" << lhs << ", " << rhs << ") = " << result
              << std::endl;
  };
  proxied_add(1, 1);
  proxied_add(1, 1);
  proxied_add(2, 3);
  proxied_add(3, 2);
  proxied_add(5, 5);

  Proxy strlen_proxy(Strlen);
  auto proxied_strlen = [&](auto str) {
    auto result = strlen_proxy(str);
    std::cout << "proxied_strlen(" << str << ") = " << result << std::endl;
  };

  proxied_strlen(std::string("hello"));
  std::string hello = "hello";
  proxied_strlen(hello);
  proxied_strlen(std::string("world"));
  std::string world = "world";
  proxied_strlen(std::move(world));
}
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
