#include "h-shell.h"


void sigFunction(int code) {
    (void)(code);
    printf("\nH-shell> ");
    fflush(stdout);
}
