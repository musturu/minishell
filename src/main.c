#include "../minishell.h"

void    read_input();


int main()
{
    read_input();
}

void    read_input()
{
    char *str;
    while (1)
    {
        str = readline("MINISHELL$>:");
        add_history(str);
        printf("readline =%s\n", str);

    }
}