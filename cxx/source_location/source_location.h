#ifndef SOURCE_LOCATION_H_
#define SOURCE_LOCATION_H_

#include <cstdint>

// A class that describes a location in source code.
struct SourceLocation {
 public:
  constexpr SourceLocation() noexcept = default;
  SourceLocation(const SourceLocation &other) = default;
  SourceLocation(SourceLocation &&other) noexcept = default;

  SourceLocation &operator=(const SourceLocation &other) = delete;
  SourceLocation &operator=(SourceLocation &&other) noexcept = delete;

  ~SourceLocation() = default;

  // NOLINTBEGIN(bugprone-easily-swappable-parameters)

  // This function should not accept any arguments.
  static constexpr SourceLocation Current(
#if __has_builtin(__builtin_LINE)
      std::uint_least32_t line = __builtin_LINE(),
#else
      std::uint_least32_t line = 0,
#endif
#if __has_builtin(__builtin_COLUMN)
      std::uint_least32_t column = __builtin_COLUMN(),
#else
      std::uint_least32_t column = 0,
#endif
#if __has_builtin(__builtin_FILE)
      const char *file_name = __builtin_FILE(),
#else
      const char *file_name = "",
#endif
#if __has_builtin(__builtin_FUNCTION)
      const char *function_name = __builtin_FUNCTION()
#else
      const char *function_name = ""
#endif
          ) noexcept {
    SourceLocation result;
    result.line_ = line;
    result.column_ = column;
    result.file_name_ = file_name;
    result.function_name_ = function_name;
    return result;
  }

  // NOLINTEND(bugprone-easily-swappable-parameters)

#if !__has_builtin(__builtin_LINE)
#warning "source_location is not well supported by the compiler."
#endif
  [[nodiscard]] constexpr std::uint_least32_t Line() const noexcept {
    return this->line_;
  }

#if !__has_builtin(__builtin_COLUMN)
#warning "source_location is not well supported by the compiler."
#endif
  [[nodiscard]] constexpr std::uint_least32_t Column() const noexcept {
    return this->column_;
  }

#if !__has_builtin(__builtin_FILE)
#warning "source_location is not well supported by the compiler."
#endif
  [[nodiscard]] constexpr const char *FileName() const noexcept {
    return this->file_name_;
  }

#if !__has_builtin(__builtin_FUNCTION)
#warning "source_location is not well supported by the compiler."
#endif
  [[nodiscard]] constexpr const char *FunctionName() const noexcept {
    return this->function_name_;
  }

 private:
  std::uint_least32_t line_ = 0;
  std::uint_least32_t column_ = 0;
  const char *file_name_ = "";
  const char *function_name_ = "";
};

#endif  // SOURCE_LOCATION_H_
