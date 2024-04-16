#include <iostream>

#include "ostream_recorder.h"

int main() {
  OstreamRecorder recorder;
  recorder.Record(std::cout) << "hello " << 1 << std::endl;
  recorder.Record(std::cerr) << "world " << 2 << std::endl;
  std::cout << "recorded:\n";
  std::cout << recorder.ToString();
}
