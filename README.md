# H-Shell

H-Shell is a custom command-line shell written in C, inspired by `bash`. It executes Unix commands, handles signals, and implements built-in commands like `cd` and `exit`. This project showcases skills in systems programming, memory management, and Unix process handling.

## Features

- **Command Execution**: Runs external commands (e.g., `ls`, `whoami`, `echo`) using `fork` and `execve`.
- **Built-in Commands**:
  - `cd`: Changes the current directory (`cd dir`, `cd`, `cd -`), with support for `$HOME` and `$OLDPWD`.
  - `exit`: Exits the shell cleanly.
- **Signal Handling**: Handles `SIGINT` (Ctrl+C), `SIGTSTP` (Ctrl+Z), and `SIGQUIT` (Ctrl+\) with custom prompts.
- **Command Counter**: Displays a command counter (`c`) for errors, mimicking `bash` behavior.
- **Robustness**:
  - Handles errors (e.g., command not found, invalid directory).
  - No memory leaks, validated by Valgrind.
  - Processes empty inputs, spaces, and non-printable characters.

## Example Usage

```bash
$ ./h-shell
H-shell> ls
README.md  exercises  h-shell  h-shell.c
H-shell> cd exercises
H-shell> ls
0.getppid  0.getppid.c
H-shell> cd -
/home/hachim/workspace/github.com/hachimB/H-shell
H-shell> whoami
hachim
H-shell> echo "How are you ?"
"How are you ?"
H-shell> ok
H-shell: 2: ok: not found
H-shell> cd ok
H-shell: cd: ok: No such file or directory
H-shell> exit
```

## Installation

### Prerequisites
- C compiler (e.g., `gcc`)
- Valgrind (for memory leak checking)
- Unix/Linux system

### Clone the repository
```bash
git clone https://github.com/hachimB/H-shell.git
```
```bash
cd H-shell
```

### Compilation
```bash
gcc -Wall -pedantic -Wextra -Werror h-shell.c signals.c utils.c -o h-shell
```

### Execution
```bash
./h-shell
```

### Memory Check with Valgrind
```bash
valgrind --leak-check=full ./h-shell
```

## Technical Challenges

- **Memory Management**: Used `malloc`, `realloc`, and `free` to manage dynamic strings without leaks, verified by Valgrind.
- **Unix Processes**: Implemented `fork` and `execve` for external commands, with proper error handling (e.g., `ENOENT` for command not found).
- **Signal Handling**: Managed `SIGINT`, `SIGTSTP`, and `SIGQUIT` with custom prompts.
- **Built-in `cd`**: Implemented `cd` with `chdir`, supporting `$HOME`, `$OLDPWD`, and error handling.
- **Robustness**: Handled edge cases (empty inputs, spaces, invalid commands) to prevent crashes.

## Code Structure

- `main.c`: Main shell loop, command parsing, and execution.
- `utils.c`: Utility functions (`easyFree`, `length`, `is_space`, `split`).
- `signals.c`: Signal handling function (`sigFunction`).
- `h-shell.h`: Header file with function prototypes and includes.

## Improvements

- Add full `$PATH` support.
- Implement additional built-ins.
- Support redirection (`>`), piping (`|`), and background processes (`&`).

## Author

- hachimB.  
- GitHub: [hachimB](https://github.com/hachimB) 
- LinkedIn: [LinkedIn](https://www.linkedin.com/in/hachim-boubacar-475831254/) 
- This project was developed as part of a portfolio project with [Boot.dev](https://www.boot.dev/).