#ifndef H_SHELL_H
#define H_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void easyFree(char **arr, char *new_line, char *line);
int length(char *str);
bool is_space(char *str);
char **split(char *str);
void sigFunction(int code);

#endif