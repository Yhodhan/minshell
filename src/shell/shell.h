#ifndef SHELL_H
#define SHELL_H

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

void shell();

#endif
