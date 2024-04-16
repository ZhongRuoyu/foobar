#include <stdio.h>
#include <unistd.h>

int puts(const char *str) {
  write(STDOUT_FILENO, "Oops!\n", 6);
  return 6;
}

int main() { printf("hello, world\n"); }
