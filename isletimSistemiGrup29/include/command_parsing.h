#ifndef COMMAND_PARSING_H
#define COMMAND_PARSING_H

#define MAX_ARGS 100

void parse_command(char *input, char **args, int *background, char **input_file, char **output_file);

#endif
