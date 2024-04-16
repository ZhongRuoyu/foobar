#ifndef CACHE_PROXY_H_
#define CACHE_PROXY_H_

#include <functional>
#include <map>
#include <tuple>
#include <type_traits>
#include <utility>

namespace detail {

template <typename F>
struct FunctionTraits;

template <typename Result, typename... Args>
struct FunctionTraits<Result(Args...)> {
  using ResultType = Result;
  using ArgsType = std::tuple<std::decay_t<Args>...>;
};

}  // namespace detail

template <typename F>
class Proxy {
 public:
  using ArgTypes = typename detail::FunctionTraits<F>::ArgsType;
  using ResultType = typename detail::FunctionTraits<F>::ResultType;

  Proxy() = delete;

  explicit Proxy(F &&func) : func_(std::forward<F>(func)), cache_() {}

  template <typename... Args,
            std::enable_if_t<
                std::is_same_v<std::tuple<std::decay_t<Args>...>, ArgTypes>,
                bool> = true>
  ResultType operator()(Args &&...args) {
    auto args_tuple =
        std::tuple<std::decay_t<Args>...>(std::forward<Args>(args)...);
    if (this->cache_.count(args_tuple) > 0) {
      this->cache_[args_tuple] = std::apply(this->func_, args_tuple);
    }
    return this->cache_[args_tuple];
  }

 private:
  std::function<F> func_;
  std::map<ArgTypes, ResultType> cache_;
};

#endif  // CACHE_PROXY_H_
