#include "shell.h"

char *get_input(char *buffer) {
  int len = 1;
  char c = ' ';
  do {
    buffer[len - 1] = c;
    buffer[len] = '\0';
    len++;
    buffer = realloc(buffer, len + 1);
  } while ((c = getchar()) != '\n');

  return buffer;
}

void parse_inputs(char *inputs) {}

void shell() {
  char *input = malloc(sizeof(char) * 2);

  printf(MAG "⋊>");
  printf(GRN " ");

  input = get_input(input);
  parse_inputs(input);

  printf(RESET "the input is: %s \n", input);
  free(input);
}
