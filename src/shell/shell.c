#include "shell.h"
#include <stdio.h>
#include <string.h>

static char *get_input(char *buffer) {
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

static char *trim(char *str) {
  int len = strlen(str);
  char *trimmed_string = malloc(len * sizeof(char));

  for (int i = 1; str[i] != '\0'; i++)
    trimmed_string[i - 1] = str[i];

  free(str);
  trimmed_string[len - 1] = '\0';
  return trimmed_string;
}

static void parse_inputs(char *inputs) {}

// Trim
// str -> " abc"
// trim_str -> "abc"

void shell() {
  for (;;) {
    char *input = malloc(sizeof(char) * 2);

    printf(MAG "⋊>");
    printf(GRN " ");

    input = get_input(input);
    input = trim(input);

    if (!strcmp(input, "exit")) {
      free(input);
      break;
    }

    parse_inputs(input);
    printf(RESET "the input is: %s \n", input);

    free(input);
  }
}
