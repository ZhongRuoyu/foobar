__asm__(".symver dlsym, dlsym@GLIBC_2.2.5");

#include <dlfcn.h>
#include <spawn.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void Debug(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "wrapper.so: ");
  vfprintf(stderr, fmt, args);
  fflush(stderr);
  va_end(args);
}

static size_t CountArgs(va_list *args) {
  va_list copy;
  va_copy(copy, *args);
  size_t count = 0;
  while (va_arg(copy, char *)) {
    ++count;
  }
  va_end(copy);
  return count;
}

static void CopyArgs(char *argv[], const char *arg0, va_list *args) {
  size_t i = 1;
  for (char *arg; (arg = va_arg(*args, char *)); ++i) {
    argv[i] = arg;
  }
  ((const char **)argv)[0] = arg0;
  ((const char **)argv)[i] = NULL;
}

int execl(const char *path, const char *arg0, ... /* , (char *)0 */) {
  va_list args;
  va_start(args, arg0);
  size_t args_count = CountArgs(&args);
  char **argv = malloc((args_count + 2) * sizeof(const char *));
  CopyArgs(argv, arg0, &args);
  va_end(args);
  int result = execv(path, argv);
  free(argv);
  return result;
}

int execle(const char *path, const char *arg0,
           ... /* , (char *)0, char *const envp[] */) {
  va_list args;
  va_start(args, arg0);
  size_t args_count = CountArgs(&args);
  char **argv = malloc((args_count + 2) * sizeof(const char *));
  CopyArgs(argv, arg0, &args);
  char **env = va_arg(args, char **);
  va_end(args);
  int result = execve(path, argv, env);
  free(argv);
  return result;
}

int execlp(const char *file, const char *arg0, ... /*, (char *)0 */) {
  va_list args;
  va_start(args, arg0);
  size_t args_count = CountArgs(&args);
  char **argv = malloc((args_count + 2) * sizeof(const char *));
  CopyArgs(argv, arg0, &args);
  va_end(args);
  int result = execvp(file, argv);
  free(argv);
  return result;
}

int execv(const char *path, char *const argv[]) {
  Debug("execv %s\n", path);
  int (*execv)(const char *path, char *const argv[]) =
      dlsym(RTLD_NEXT, "execv");
  return execv(path, argv);
}

int execve(const char *path, char *const argv[], char *const envp[]) {
  Debug("execve %s\n", path);
  int (*execve)(const char *path, char *const argv[], char *const envp[]) =
      dlsym(RTLD_NEXT, "execve");
  return execve(path, argv, envp);
}

int execvp(const char *file, char *const argv[]) {
  Debug("execvp %s\n", file);
  int (*execvp)(const char *file, char *const argv[]) =
      dlsym(RTLD_NEXT, "execvp");
  return execvp(file, argv);
}

int fexecve(int fd, char *const argv[], char *const envp[]) {
  Debug("fexecve %d\n", fd);
  int (*fexecve)(int fd, char *const argv[], char *const envp[]) =
      dlsym(RTLD_NEXT, "fexecve");
  return fexecve(fd, argv, envp);
}

int posix_spawn(pid_t *restrict pid, const char *restrict path,
                const posix_spawn_file_actions_t *file_actions,
                const posix_spawnattr_t *restrict attrp,
                char *const argv[restrict], char *const envp[restrict]) {
  Debug("posix_spawn %s\n", path);
  int (*posix_spawn)(pid_t *restrict pid, const char *restrict path,
                     const posix_spawn_file_actions_t *file_actions,
                     const posix_spawnattr_t *restrict attrp,
                     char *const argv[restrict], char *const envp[restrict]) =
      dlsym(RTLD_NEXT, "posix_spawn");
  return posix_spawn(pid, path, file_actions, attrp, argv, envp);
}

int posix_spawnp(pid_t *restrict pid, const char *restrict file,
                 const posix_spawn_file_actions_t *file_actions,
                 const posix_spawnattr_t *restrict attrp,
                 char *const argv[restrict], char *const envp[restrict]) {
  Debug("posix_spawnp %s\n", file);
  int (*posix_spawnp)(pid_t *restrict pid, const char *restrict file,
                      const posix_spawn_file_actions_t *file_actions,
                      const posix_spawnattr_t *restrict attrp,
                      char *const argv[restrict], char *const envp[restrict]) =
      dlsym(RTLD_NEXT, "posix_spawnp");
  return posix_spawnp(pid, file, file_actions, attrp, argv, envp);
}
