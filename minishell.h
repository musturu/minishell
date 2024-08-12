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

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
// Definizioni di prototipi di funzione, se necessario
// ...


typedef enum{
    TOKEN_WORD,         //  o comando o file ??
    TOKEN_PIPE,         //      = |
    TOKEN_REDIR_IN,     //     = >
    TOKEN_REDIR_OUT,    //     = <
    TOKEN_REDIR_APPEND, //  = >>
    TOKEN_REDIR_PRE,    //     = <<
    TOKEN_EOF,          // END OF FILE
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_DOLLAR,
    TOKEN_OPEN_P,
    TOKEN_CLOSE_P,
    // Aggiungere altri tipi di token necessari
} TokenType;

typedef enum{
    COM_NAME,
    COM_ARGS,
    FILE,
} WordType;

typedef struct s_token
{
    TokenType   type;
    char        *value;
} token;

typedef struct s_token_list
{
    token   token;
    struct s_token_list    *next;
    struct s_token_list    *prev;
}   t_token_list;

/*TOKENIZER*/
void    go_next(char **str);
int space_until_next(char   *str);
t_list    *tokenize(char   *str, t_list  *list);

/*debug*/
void    print_list(t_list *list);


#endif