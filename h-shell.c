#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

// Counts the number of character in a string
int length(char *str) {
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}


// Checks if a string contains just spaces. 
bool is_space(char* str) {
    int i = 0;
    while(str[i] != 0) {
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
    // int count = 0;
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


void sigFunction(int code) {
    printf("\nH-shell> ");
    fflush(stdout);
}


// Main function
int main(int argc, char *argv[]) {
    
    signal(SIGINT, sigFunction);
    signal(SIGTSTP, sigFunction);
    signal(SIGQUIT, sigFunction);
    while(1) {
        printf("H-shell> ");

        char *line = NULL;
        size_t len = 0;
        signal(SIGTSTP, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        ssize_t chars_read = getline(&line, &len, stdin);
        
        if (chars_read == -1) {
            if (errno == EINTR) {
                free(line);
                continue;
            }
            printf("\n");
            free(line);
            exit(0);
        }
        else {
            int line_length = length(line) - 1;
            char *new_line = malloc((line_length + 1)* sizeof(char));
            if (!new_line) return 1;

            int k = 0;
            for (int i = 0; i < line_length; i++) {
                if (isprint(line[i])) {
                    new_line[k] = line[i];
                    k++;
                }
            }
            new_line[k] = '\0';


            if (new_line[0] == '\0') {
                free(new_line);
                free(line);
                continue;
            }

            if (is_space(new_line)) {
                free(new_line);
                free(line);
                continue;
            }

            char **arr = split(new_line);
            if (!arr) {
                free(new_line);
                free(line);
                return 1;
            }

            int i = 0;
            while(arr[i] != NULL) {
                i++;
            }
            
            if (strcmp(arr[0], "exit") == 0) {
                for (int j = 0; j < i; j++) {
                free(arr[j]);
                }
                free(new_line);
                free(arr);
                free(line);

                exit(0);
            }

            if (arr[0] == NULL) {
                for (int j = 0; j < i; j++) {
                free(arr[j]);
                }
                free(new_line);
                free(arr);
                free(line);
                continue;
            }

            printf("%d\n", i);
            
            for (int j = 0; j < i; j++) {
                printf("[%s]\n", arr[j]);
            }

            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            free(new_line);
            free(line);
        }
    }
    return (0);
}
