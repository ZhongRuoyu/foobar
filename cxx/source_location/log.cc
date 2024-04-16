#include <iostream>
#include <ostream>

#include "source_location.h"

std::ostream &Log(SourceLocation source_location = SourceLocation::Current()) {
  return std::cout << "(" << source_location.FileName() << ":"
                   << source_location.Line() << ":" << source_location.Column()
                   << " " << source_location.FunctionName() << ") ";
}

void Foo(int num) { Log() << "Foo(" << num << ")" << std::endl; }

int main() {
  Foo(42);
  Log() << "hello, world" << std::endl;
}
