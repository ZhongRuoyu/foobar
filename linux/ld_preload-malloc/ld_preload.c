#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  kInitialBufferCount = 16,
};
struct Buffer {
  void *ptr;
  size_t size;
};
static struct Buffer **buffers = NULL;
static size_t buffer_slots = 0;
static size_t buffer_count = 0;

static int initializing = 0;
static void *(*real_malloc)(size_t) = NULL;
static void (*real_free)(void *) = NULL;
static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_realloc)(void *, size_t) = NULL;
static void *(*real_reallocarray)(void *, size_t, size_t) = NULL;

__attribute__((constructor)) static void Init() {
  initializing = 1;

  real_malloc = dlsym(RTLD_NEXT, "malloc");
  real_free = dlsym(RTLD_NEXT, "free");
  real_calloc = dlsym(RTLD_NEXT, "calloc");
  real_realloc = dlsym(RTLD_NEXT, "realloc");
  real_reallocarray = dlsym(RTLD_NEXT, "reallocarray");

  if (real_malloc == NULL || real_free == NULL || real_calloc == NULL ||
      real_realloc == NULL || real_reallocarray == NULL) {
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    fprintf(stderr, "Error: dlsym: %s\n", dlerror());
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    exit(EXIT_FAILURE);
  }

  initializing = 0;
}

static void RecordAllocation(void *buffer, size_t size) {
  if (buffer_slots == 0) {
    buffer_slots = kInitialBufferCount;
    buffers = real_malloc(kInitialBufferCount * sizeof(struct Buffer *));
  }
  if (buffer_count == buffer_slots) {
    struct Buffer **new_buffers =
        real_realloc(buffers, buffer_slots * 2 * sizeof(struct Buffer *));
    if (new_buffers == NULL) {
      perror("Error reallocating memory for buffers");
      // NOLINTNEXTLINE(concurrency-mt-unsafe)
      exit(EXIT_FAILURE);
    }
    buffers = new_buffers;
    buffer_slots *= 2;
  }
  struct Buffer *entry = real_malloc(sizeof(struct Buffer));
  if (entry == NULL) {
    perror("Error reallocating memory for entry");
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    exit(EXIT_FAILURE);
  }
  entry->ptr = buffer;
  entry->size = size;
  buffers[buffer_count] = entry;
  ++buffer_count;
}

void *malloc(size_t size) {
  if (real_malloc == NULL) {
    static char static_buf[4096];
    static size_t static_buf_pos = 0;
    if (static_buf_pos + size > sizeof(static_buf)) {
      fprintf(stderr, "Insufficient memory for static allocation\n");
      // NOLINTNEXTLINE(concurrency-mt-unsafe)
      exit(EXIT_FAILURE);
    }
    void *ptr = static_buf + static_buf_pos;
    static_buf_pos += size;
    return ptr;
  }

  void *ptr = real_malloc(size);
#ifdef VERBOSE
  fprintf(stderr, "malloc(%lu) = %p\n", size, ptr);
#endif  // VERBOSE
  RecordAllocation(ptr, size);
  return ptr;
}

void free(void *ptr) {
#ifdef VERBOSE
  fprintf(stderr, "free(%p)\n", ptr);
#endif  // VERBOSE
  // Do not actually free ptr.
}

void *calloc(size_t nmemb, size_t size) {
  if (real_calloc == NULL) {
    void *ptr = malloc(nmemb * size);
    if (ptr != NULL) {
      memset(ptr, 0, nmemb * size);
    }
    return ptr;
  }

  void *ptr = real_calloc(nmemb, size);
  RecordAllocation(ptr, nmemb * size);
#ifdef VERBOSE
  fprintf(stderr, "calloc(%lu, %lu) = %p\n", nmemb, size, ptr);
#endif  // VERBOSE
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  for (size_t i = 0; i < buffer_count; ++i) {
    struct Buffer *entry = buffers[i];
    if (entry->ptr == ptr) {
      void *new_ptr = real_realloc(ptr, size);
      entry->ptr = new_ptr;
      entry->size = size;
#ifdef VERBOSE
      fprintf(stderr, "realloc(%p, %lu) = %p\n", ptr, size, new_ptr);
#endif  // VERBOSE
      return new_ptr;
    }
  }
  return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  void *new_ptr = reallocarray(ptr, nmemb, size);
#ifdef VERBOSE
  fprintf(stderr, "reallocarray(%p, %lu, %lu) = %p\n", ptr, nmemb, size,
          new_ptr);
#endif  // VERBOSE
  return new_ptr;
}

__attribute__((destructor)) static void Dump() {
  for (size_t i = 0; i < buffer_count; ++i) {
    struct Buffer *entry = buffers[i];
    fprintf(stderr, "%lu/%lu: %p (size = %lu): %s\n", i + 1, buffer_count,
            entry->ptr, entry->size, (char *)(entry->ptr));
    // real_free(entry->ptr);
  }
  // Leave it to the OS to do the cleanup. If we call free ourselves, we could
  // encounter segfault due to messing with dynamic linker internals.
}
