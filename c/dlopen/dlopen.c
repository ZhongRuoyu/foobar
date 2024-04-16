// https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/DynamicLibraries/100-Articles/DynamicLibraryUsageGuidelines.html

#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#define LIBCURL "libcurl.4.dylib"
#else
#define LIBCURL "libcurl.so.4"
#endif

int main() {
  void *libcurl_handle = dlopen(LIBCURL, RTLD_LAZY | RTLD_LOCAL);
  if (libcurl_handle == NULL) {
    printf("[%s] Unable to open %s: %s\n", __FILE__, LIBCURL, dlerror());
    exit(1);
  }

  char *(*curl_version)(void) =
      (char *(*)(void))dlsym(libcurl_handle, "curl_version");
  if (curl_version != NULL) {
    printf("[%s] curl_version() returned: %s\n", __FILE__, curl_version());
  } else {
    printf("[%s] Unable to find curl_version: %s\n", __FILE__, dlerror());
  }
  dlclose(libcurl_handle);
}
