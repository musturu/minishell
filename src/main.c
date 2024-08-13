#include "../minishell.h"

void    read_input();


int main()
{
    read_input();
}

void    print_list(t_list *list)
{
    t_list  *tmp = list;
    token   *tkn;

    while (tmp)
    {
        tkn = tmp->content;
        printf("TOKENTYPE: %i\tTOKENVALUE:<%s>\n", tkn->type, tkn->value);
        tmp = tmp->next;
    }
}

void    read_input()
{
    char *str;
    t_list *list;

    list = NULL;
    while (1)
    {
        str = readline("MINISHELL$>:");
        add_history(str);
        list = tokenize(str, &list);
        printf("uscito da tokenize\n");
        print_list(list);
        parser(list);
    }
}
