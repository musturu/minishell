#include "../minishell.h"
#include <curses.h>
#include <stdio.h>

void    read_input();

void ft_zozzle()
{
    printf("\n"PROMPT" ");
}

void    ft_signals()
{

    signal(SIGINT, ft_zozzle);
    signal(SIGKILL, ft_zozzle);
}

int main()
{
    ft_signals();
    read_input();
}

void    print_parse(t_list *list)
{
    t_list  *tmp = list;
    command     *cmd;

    while (tmp)
    {
        printf("NEW COMMAND\n");
        cmd = tmp->content;
        printf("CMD: %s\n", cmd->cmd);
		printf("\n\tINPATH:%s -----> OUTPATH:%s\n", cmd->inpath, cmd->outpath);
		if (cmd->inconnect)
			printf("CONNECTOR IN: %i (1 = PIPE, 7 = &)\n", cmd->inconnect);
		if (cmd->outconnect)
			printf("CONNECTOR OUT: %i\n", cmd->outconnect);
        while (cmd->args)
        {
            printf("\tARG: %s\n",  (char *)cmd->args->content);
            cmd->args = cmd->args->next;
        }
        tmp = tmp->next;
    }
}

void    print_tokens(t_list *list)
{
    t_list  *tmp = list;
    token   *tkn;

    while (tmp)
    {
        tkn = tmp->content;
        printf("TOKENTYPE: %i\tTOKENVALUE:<%s> prev :%p - cur :%p \n", tkn->type, tkn->value, tmp->prev, tmp);
        tmp = tmp->next;
    }
}

int blank_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}


void    read_input()
{
    char *str;
    t_list *tlist;
    t_list *plist;

    tlist = NULL;
	plist = NULL;
    while (1)
    {
        str = readline(PROMPT" ");
        add_history(str);
        if (blank_check(str))
            continue;
        tlist = tokenize(str, &tlist);
        print_tokens(tlist);
        plist = parser(&tlist, &plist);
		if (plist == NULL)
			printf("syntax error\n");
        print_parse(plist);
        ft_lstclear(&tlist, free);
        ft_lstclear(&plist, free);
        tlist = NULL;
		plist = NULL;
    }
}
