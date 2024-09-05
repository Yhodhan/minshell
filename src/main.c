#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Shell's colors
#define RED "\x1B[31m"
#define MAG "\x1B[35m"
#define RESET "\x1B[0m"
#define GRN "\x1B[32m"

char *get_input(char *buffer) {
  int len = 1;
  char c = ' ';
  while ((c = getchar()) != '\n') {
    buffer[len - 1] = c;
    buffer[len] = '\0';
    len++;
    buffer = realloc(buffer, len + 1);
  }
  return buffer;
}

void parse_inputs(char *inputs) {}

void shell() {
  char *str = malloc(sizeof(char) * 2);

  printf(MAG "⋊>");
  printf(GRN " ");

  str = get_input(str);
  parse_inputs(str);

  printf(RESET "the str is: %s \n", str);
  free(str);
}

int main(int argc, char **argv) {
  shell();
  return 0;
}
