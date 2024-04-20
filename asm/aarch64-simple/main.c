#include <stdio.h>

extern long long Strlen(const char *s);

extern int Sum(const int *arr, long long size);

int main(int argc, char **argv) {
  char str[] = "hello, world";
  // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  printf("Strlen(str) = %lld\n", Strlen(str));
  // printf("Sum(arr, size) = %d\n", Sum(arr, sizeof(arr) / sizeof(*arr)));
  return 0;
}
