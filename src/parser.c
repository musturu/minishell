/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:52:52 by mamerlin          #+#    #+#             */
/*   Updated: 2024/08/19 02:58:05 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int parse_dollar(void)
{
	return (1);
}

static int check_error(int i)
{
	if (i == 0)
	{
		printf("Error");
		return (1);
	}
	return (0);
}


static int parser_DBQ(t_list **list)
{
	token *tkn;

	tkn = (*list)->content;
	if (tkn->type == TOKEN_DOLLAR)
		parse_dollar();
	tkn->type = COM_ARGS;
	(*list) = (*list)->next;
	while (tkn->type != TOKEN_DBQUOTE)
	{
		tkn = (*list)->content;
		if (tkn->type == TOKEN_EOF)
			return (0);
		tkn->type = COM_ARGS;
		(*list) = (*list)->next;
	}
	tkn->type = COM_ARGS;
	return (1);
}

/*
static int parser_space(t_list **list)
{
	token *tkn;

	tkn = (*list)->content;
	if ((*list)->prev->content == NULL)
		tkn->type = COM_ARGS;
	return (0);
}
*/

//problema echo "tfyv\"dbh" 
static int parser_backslash_dbquote(t_list **list)
{
	token *tkn;
	token *tkn_next;
	t_list *tmp;
	int i;

	i = 1;
	tmp = *list;
	tkn = (*list)->content;
	tkn_next = (*list)->next->content;
	while (tkn->type != TOKEN_DBQUOTE)
	{
		if (tkn_next->type == TOKEN_DOLLAR || tkn_next->type == TOKEN_DBQUOTE)
			tkn->type = TOKEN_DELETE;
		else if (tkn_next->type == TOKEN_BACKSLASH)
		{
			while(tkn_next == TOKEN_BACKSLASH)
			{
				tmp = tmp->next;
				i++;
			}
			if (i % 2 == 0)
			{
				while(tkn_next == TOKEN_BACKSLASH)
				{
					tkn->type = COM_ARGS;
					tkn_next->type = TOKEN_DELETE;
					(*list) = (*list)->next->next;
				}
			}
			else
				printf("Error");
		}
		else
			tkn->type = COM_ARGS;
		(*list) = (*list)->next;
	}
	return (1);
}

static int parser_backslash_squote(t_list **list)
{
	token *tkn;
	token *tkn_next;
	t_list *tmp;
	int i;

	i = 1;
	tmp = *list;
	tkn = (*list)->content;
	tkn_next = (*list)->next->content;
	if (tkn_next->type == TOKEN_DOLLAR || tkn_next->type == TOKEN_SQUOTE)
		tkn->type = TOKEN_DELETE;
	else if (tkn_next->type == TOKEN_BACKSLASH)
	{
		while(tkn_next == TOKEN_BACKSLASH)
		{
			tmp = tmp->next;
			i++;
		}
		if (i % 2 == 0)
		{
			while(tkn_next == TOKEN_BACKSLASH)
			{
				tkn->type = COM_ARGS;
				tkn_next->type = TOKEN_DELETE;
				(*list) = (*list)->next->next;
			}
		}
		else
			printf("Error");
	}
	else
		tkn->type = COM_ARGS;
	return (1);
}

static int parser_SQ(t_list **list)
{
	token *tkn;
	token *tkn_next;

	tkn = (*list)->content;
	tkn->type = COM_ARGS;
	(*list) = (*list)->next;
	while (tkn->type != TOKEN_SQUOTE)
	{
		tkn = (*list)->content;
		if(tkn->type == TOKEN_BACKSLASH)
			parser_backslash_squote(list);
		else
			tkn->type = COM_ARGS;
		(*list) = (*list)->next;
	}
	return (1);
}

static int parser_backslash(t_list **list)
{
	token *tkn;
	token *tkn_next;

	tkn = (*list)->content;
	tkn_next = (*list)->next->content;
	if(tkn_next->type == TOKEN_BACKSLASH)
	{
		tkn->type = COM_ARGS;
		tkn_next->type = TOKEN_DELETE;
	}
	else if (tkn_next->type == TOKEN_DOLLAR || tkn_next->type == TOKEN_DBQUOTE)
		return (0);
}



t_list	*parser(t_list *tokens)
{
	token   *tkn;
	t_list	*list;

	list = tokens;
	printf("nel parser\n");
	print_list(list);
	while(list)
	{
		printf("test\n");
		print_list(list);
		printf("test\n");
		tkn = list->content;
		if ((*list).prev == NULL)
			tkn->type = COM_NAME;
		//else if (tkn->type == TOKEN_SPACE)
			//check_error(parser_space(&list));
		else if (tkn->type == TOKEN_SQUOTE)
			check_error(parser_SQ(&list));
		else if (tkn->type == TOKEN_DBQUOTE)
			check_error(parser_DBQ(&list));
		else if (tkn->type == TOKEN_BACKSLASH)
			check_error(parser_backslash(&list));
		else
			tkn->type = COM_ARGS;
		list = list->next;
	}
	return (list);
}

