#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

char *GetLine(int display) {
  struct termios old_termios;
  if (!display) {
    if (tcgetattr(STDIN_FILENO, &old_termios) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
    struct termios new_termios = old_termios;
    new_termios.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1) {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }

  char *result = NULL;
  size_t n;
  if (getline(&result, &n, stdin) == -1) {
    free(result);
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  char *newline = strchr(result, '\n');
  if (newline != NULL) {
    *newline = '\0';
  }

  if (!display) {
    printf("\n");
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_termios) == -1) {
      free(result);
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  }

  return result;
}

int GetAnyKey() {
  struct termios old_termios;
  if (tcgetattr(STDIN_FILENO, &old_termios) == -1) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  struct termios new_termios = old_termios;
  new_termios.c_lflag &= ~ECHO;
  new_termios.c_lflag &= ~ICANON;
  if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  int result = getchar();

  if (tcsetattr(STDIN_FILENO, TCSANOW, &old_termios) == -1) {
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  return result;
}

int main(void) {
  printf("Username: ");
  char *username = GetLine(1);
  printf("Password: ");
  char *password = GetLine(0);
  printf("Read username: %s\n", username);
  printf("Read password: %s\n", password);
  free(username);
  free(password);
  printf("Press any key to continue... ");
  GetAnyKey();
  printf("\n");
  return 0;
}
