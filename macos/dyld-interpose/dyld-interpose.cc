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
  std::string wrapper_dylib_path = std::filesystem::canonical(
      std::filesystem::path(argv[0]).parent_path() / "wrapper.dylib",
      error_code);
  if (error_code) {
    std::cerr << error_code.message() << "\n";
    exit(EXIT_FAILURE);
  }

  std::string dyld_force_flat_namespace_env = "DYLD_FORCE_FLAT_NAMESPACE=1";
  putenv(const_cast<char *>(dyld_force_flat_namespace_env.c_str()));
  std::cout << dyld_force_flat_namespace_env << "\n";

  std::string dyld_insert_libraries_env =
      "DYLD_INSERT_LIBRARIES=" + wrapper_dylib_path;
  putenv(const_cast<char *>(dyld_insert_libraries_env.c_str()));
  std::cout << dyld_insert_libraries_env << "\n";

  return execvp(argv[1], argv + 1);
}
