#include <stdlib.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>

int main(int argc, char **argv) {
  if (argc <= 1) {
    std::cerr << "Usage: " << argv[0] << " <command> [args...]\n";
    exit(EXIT_FAILURE);
  }

  std::error_code error_code;
  std::string wrapper_so_path = std::filesystem::canonical(
      std::filesystem::path(argv[0]).parent_path() / "wrapper.so", error_code);
  if (error_code) {
    std::cerr << error_code.message() << "\n";
    exit(EXIT_FAILURE);
  }

  std::string ld_preload_env = "LD_PRELOAD=" + wrapper_so_path;
  putenv(const_cast<char *>(ld_preload_env.c_str()));
  std::cout << ld_preload_env << "\n";

  return execvp(argv[1], argv + 1);
}
