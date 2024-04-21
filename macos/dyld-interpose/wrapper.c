#include <dlfcn.h>
#include <spawn.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dyld-interposing.h"

static void Debug(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "wrapper.dylib: ");
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

int Execl(const char *path, const char *arg0, ... /* , (char *)0 */) {
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
DYLD_INTERPOSE(Execl, execl);

int Execle(const char *path, const char *arg0,
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
DYLD_INTERPOSE(Execle, execle);

int Execlp(const char *file, const char *arg0, ... /*, (char *)0 */) {
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
DYLD_INTERPOSE(Execlp, execlp);

int Execv(const char *path, char *const argv[]) {
  Debug("execv %s\n", path);
  return execv(path, argv);
}
DYLD_INTERPOSE(Execv, execv);

int Execve(const char *path, char *const argv[], char *const envp[]) {
  Debug("execve %s\n", path);
  return execve(path, argv, envp);
}
DYLD_INTERPOSE(Execve, execve);

int Execvp(const char *file, char *const argv[]) {
  Debug("execvp %s\n", file);
  return execvp(file, argv);
}
DYLD_INTERPOSE(Execvp, execvp);

int PosixSpawn(pid_t *restrict pid, const char *restrict path,
               const posix_spawn_file_actions_t *file_actions,
               const posix_spawnattr_t *restrict attrp,
               char *const argv[restrict], char *const envp[restrict]) {
  Debug("posix_spawn %s\n", path);
  return posix_spawn(pid, path, file_actions, attrp, argv, envp);
}
DYLD_INTERPOSE(PosixSpawn, posix_spawn);

int PosixSpawnp(pid_t *restrict pid, const char *restrict file,
                const posix_spawn_file_actions_t *file_actions,
                const posix_spawnattr_t *restrict attrp,
                char *const argv[restrict], char *const envp[restrict]) {
  Debug("posix_spawnp %s\n", file);
  return posix_spawnp(pid, file, file_actions, attrp, argv, envp);
}
DYLD_INTERPOSE(PosixSpawnp, posix_spawnp);
