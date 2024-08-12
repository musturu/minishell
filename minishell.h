#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>          // Per printf, perror
# include <stdlib.h>         // Per malloc, free, exit, getenv
# include <unistd.h>         // Per write, access, read, close, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty, ttyname, ttyslot
# include <string.h>         // Per strerror
# include <fcntl.h>          // Per open
# include <sys/wait.h>       // Per wait, waitpid, wait3, wait4
# include <signal.h>         // Per signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>       // Per stat, lstat, fstat
# include <dirent.h>         // Per opendir, readdir, closedir
# include <sys/ioctl.h>      // Per ioctl
# include <termios.h>        // Per tcsetattr, tcgetattr
# include <curses.h>         // Per alcune funzioni termcap
# include <term.h>           // Per altre funzioni termcap

// Inclusioni per readline
# include <readline/readline.h>
# include <readline/history.h>

// Definizioni di prototipi di funzione, se necessario
// ...

typedef struct t_command {
    char    *cmd;
    char    *arg;
    int     infd;
    int     outfd;
}

#endif // MINISHELL_H