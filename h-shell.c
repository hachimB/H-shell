#include "h-shell.h"


int main(int argc, char *argv[]) {
    
    signal(SIGINT, sigFunction);
    signal(SIGTSTP, sigFunction);
    signal(SIGQUIT, sigFunction);
    pid_t pid;
    int c = 1;
    int status;

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
                easyFree(arr, new_line, line);
                exit(0);
            }

            if (strcmp(arr[0], "cd") == 0) {
                char* directory = arr[1]? arr[1]:getenv("HOME");
                char buffer[256];

                if (!directory) {
                    c++;
                    easyFree(arr, new_line, line);
                    continue;  
                }

                if (getcwd(buffer, sizeof(buffer)) == NULL) {
                    perror("getcwd error");
                    c++;
                    easyFree(arr, new_line, line);
                    continue;
                }

                if (directory && strcmp(directory, "-") == 0) {
                    directory = getenv("OLDPWD");
                    if (directory) {
                        printf("%s\n", directory);
                    }
                    else {
                        printf("H-shell: cd: OLDPWD not set\n");
                        c++;
                        easyFree(arr, new_line, line);
                        continue;
                    }
                }

                if (chdir(directory) == -1){
                    printf("H-shell: cd: %s: No such file or directory\n", directory);
                } else {
                    setenv("OLDPWD", buffer, 1);
                }
                c++;
                easyFree(arr, new_line, line);
                continue;
            }


            if (arr[0] == NULL) {
                easyFree(arr, new_line, line);
                continue;
            }


//--------- Execution [fork()]

            pid = fork();
            if (pid == -1) {
                easyFree(arr, new_line, line);
                exit(1); //EXIT_FAILURE
            }

            else if (pid == 0) {
                char path[256];
                snprintf(path, sizeof(path), "/bin/%s", arr[0]);
                int exe = execve(path, arr, NULL);

                if (exe == -1) {
                    if(errno == ENOENT) {
                        easyFree(arr, new_line, line);
                        exit(127);
                    }
                    else {
                        easyFree(arr, new_line, line);
                        exit(1);
                    }
                }
            }

            else {
                wait(&status);
                if(WEXITSTATUS(status) == 127) {
                    printf("H-shell: %d: %s: not found\n", c, arr[0]);
                }
                c++;
                easyFree(arr, new_line, line);
                continue;
            }

//---------

            easyFree(arr, new_line, line);
        }
    }
    return (0);
}
