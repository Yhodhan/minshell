#include "shell.h"
#include <stdio.h>
#include <string.h>

static void get_input(char **input)
{
    char *buffer = malloc(sizeof(char) * 2);
    int len = 1;
    char c = ' ';
    do
    {
        buffer[len - 1] = c;
        buffer[len] = '\0';
        len++;
        buffer = realloc(buffer, len + 1);
    } while ((c = getchar()) != '\n');

    *input = buffer;
}

// Trim
// str -> " abc"
// trim_str -> "abc"
static char *trim(char *str)
{
    int len = strlen(str);
    char *trimmed_string = malloc(len * sizeof(char));

    for (int i = 1; str[i] != '\0'; i++)
        trimmed_string[i - 1] = str[i];

    free(str);
    trimmed_string[len - 1] = '\0';
    return trimmed_string;
}

static int has_white_spaces(char *args)
{
    int len = strlen(args);
    for (int i = 0; i < len; i++)
    {
        if (args[i] == ' ')
            return 1;
    }
    return 0;
}

void copy_commands(char *inputs, Set *args, int len, int last_char_pos)
{
    char *buffer = malloc(len * sizeof(char) + 1);
    for (int i = 0; i < len; i++)
    {
        buffer[i] = inputs[last_char_pos];
        last_char_pos++;
    }
    buffer[len] = '\0';
    add(args, buffer);
}

// "ls -a -l" -> {"ls", "-a", "-l"}
static Set parse_inputs(char *inputs)
{
    Set args = init_set();
    // check if the command has spaces
    if (!has_white_spaces(inputs))
    {
        int len = strlen(inputs);
        copy_commands(inputs, &args, len, 0);
    }
    else
    {
        // else is an explit command
        int last_char_pos = 0;
        int i = 0;
        for (; inputs[i] != '\0'; i++)
        {
            if (inputs[i] == ' ')
            {
                copy_commands(inputs, &args, (i - last_char_pos), last_char_pos);
                last_char_pos = i + 1;
            }
        }
        // copy the remaining arguments
        copy_commands(inputs, &args, (i - last_char_pos), last_char_pos);
    }
    free(inputs);
    return args;
}

void exec(char **args)
{
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork did not work");
        break;
    case 0:
        execvp(args[0], args);
    }
}

unsigned short end(char *input)
{
    if (!strcmp(input, "exit") || !strcmp(input, "quit") || !strcmp(input, "q"))
        return 1;
    else
        return 0;
}

void shell()
{
    for (;;)
    {
        char *input = NULL;
        printf(MAG "⋊> ");
        printf(GRN "");

        get_input(&input);
        input = trim(input);

        printf(WHT "");
        fflush(stdout);

        if (end(input))
        {
            free(input);
            break;
        }

        Set parsed_args = parse_inputs(input);
        char **args = to_array(&parsed_args);

        // exec command
        exec(args);
        wait(NULL);

        delete_set(&parsed_args);
        free(args);
    }

    fflush(stdout);
}
