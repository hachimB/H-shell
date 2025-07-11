#include "h-shell.h"

void easyFree(char **arr, char *new_line, char *line) {
    for (int j = 0; arr[j] != NULL; j++) {
        free(arr[j]);
    }
    free(new_line);
    free(arr);
    free(line);
}

int length(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

bool is_space(char *str) {
    int i = 0;
    while (str[i] != 0) {
        if (str[i] != ' ') {
            return false;
        }
        i++;
    }
    return true;
}

// Splits a string into tokens using strtok(), adds each token in an array and returns it. 
char **split(char *str) {
    if (!str) return NULL;
    char **arr = malloc(sizeof(char*));
    if (!arr) return NULL;
    int i = 0;
    char *token;
    char **temp;
    char *delim = " ";

    char *strToken = strtok(str, delim);
    if (!strToken) {
        free(arr);
        return NULL;
    }
    
    while(strToken) {
        if (strToken[0] == '\0') continue;

        token = strdup(strToken);
        temp = realloc(arr, (i + 2) * sizeof(char*));
        if (!temp) {
            free(arr);
            free(token);
            return NULL;
        }
        arr = temp;
        arr[i] = token;
        arr[i + 1] = NULL;
        strToken = strtok(NULL, delim);
        i++;
    }
    return arr;
}