#ifndef OSTREAM_RECORDER_H_
#define OSTREAM_RECORDER_H_

#include <functional>
#include <ios>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <utility>

template <typename CharT, typename Traits = std::char_traits<CharT>>
class BasicOstreamRecorder {
 public:
  class Proxy : private std::basic_streambuf<CharT, Traits>,
                public std::basic_ostream<CharT, Traits> {
   public:
    friend BasicOstreamRecorder;

    Proxy() = delete;
    Proxy(const Proxy &other) = delete;
    Proxy(Proxy &&other) noexcept
        : std::basic_streambuf<CharT, Traits>(other),
          std::basic_ostream<CharT, Traits>(std::move(other)),
          recorder_(other.recorder_),
          ostream_(other.ostream_),
          stringstream_(std::move(other.stringstream_)) {}

    Proxy &operator=(const Proxy &other) = delete;
    Proxy &operator=(Proxy &&other) = delete;

    ~Proxy() override {
      this->stringstream_.flush();
      this->stringstream_.seekg(0);
      this->ostream_.get() << this->stringstream_.rdbuf();
      this->stringstream_.seekg(0);
      this->recorder_.get().ostringstream_ << this->stringstream_.rdbuf();
    }

    template <typename T>
    Proxy &operator<<(T &&value) {
      this->stringstream_ << std::forward<T>(value);
      return *this;
    }

    Proxy &operator<<(std::ios_base &(*func)(std::ios_base &)) {
      this->stringstream_ << func;
      return *this;
    }

    Proxy &operator<<(std::basic_ios<CharT, Traits> &(*func)(
        std::basic_ios<CharT, Traits> &)) {
      this->stringstream_ << func;
      return *this;
    }

    Proxy &operator<<(std::basic_ostream<CharT, Traits> &(*func)(
        std::basic_ostream<CharT, Traits> &)) {
      this->stringstream_ << func;
      return *this;
    }

   private:
    explicit Proxy(BasicOstreamRecorder &recorder,
                   std::basic_ostream<CharT, Traits> &ostream)
        : std::basic_ostream<CharT, Traits>(this),
          ostream_(ostream),
          recorder_(recorder) {}

    std::reference_wrapper<BasicOstreamRecorder> recorder_;
    std::reference_wrapper<std::basic_ostream<CharT, Traits>> ostream_;
    std::basic_stringstream<CharT, Traits> stringstream_;
  };

  BasicOstreamRecorder() = default;
  BasicOstreamRecorder(const BasicOstreamRecorder &other) = delete;
  BasicOstreamRecorder(BasicOstreamRecorder &&other) noexcept
      : ostringstream_(std::move(other.ostringstream_)) {}

  BasicOstreamRecorder &operator=(const BasicOstreamRecorder &other) = delete;
  BasicOstreamRecorder &operator=(BasicOstreamRecorder &&other) noexcept {
    this->ostringstream_ = std::move(other.ostringstream_);
    return *this;
  }

  ~BasicOstreamRecorder() = default;

  Proxy Record(std::basic_ostream<CharT, Traits> &ostream) {
    return Proxy(*this, ostream);
  }

  void Clear() { this->ostringstream_.str(std::string()); }

  [[nodiscard]] std::string ToString() const {
    return this->ostringstream_.str();
  }

 private:
  std::basic_ostringstream<CharT, Traits> ostringstream_;
};

using OstreamRecorder = BasicOstreamRecorder<char>;

#endif  // OSTREAM_RECORDER_H_
