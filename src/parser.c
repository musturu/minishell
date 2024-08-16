/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:52:52 by mamerlin          #+#    #+#             */
/*   Updated: 2024/08/16 20:41:14 by mamerlin         ###   ########.fr       */
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
	tkn->type == COM_ARGS;
	(*list) = (*list)->next;
	while (tkn->type != TOKEN_DBQUOTE)
	{
		tkn = (*list)->content;
		if (tkn->type == TOKEN_EOF)
			return (0);
		tkn->type == COM_ARGS;
		(*list) = (*list)->next;
	}
	(*list)->content = COM_ARGS;
	return (1);
}

static int parser_space(t_list **list)
{
	if ((*list)->prev->content == COM_NAME)
		(*list)->content = COM_ARGS;
	return (0);
}

static int parser_SQ(t_list **list)
{
	token *tkn;

	tkn = (*list)->content;
	tkn->type = COM_ARGS;
	(*list) = (*list)->next;
	while (tkn->type != TOKEN_SQUOTE)
	{
		tkn = (*list)->content;
		if (tkn->type == TOKEN_EOF)
			return (0);
		tkn->type == COM_ARGS;
		(*list) = (*list)->next;
	}
	tkn->type = COM_ARGS;
	return (1);
}

t_list	*parser(t_list *tokens)
{
	token   *tkn;
	t_list	*list;

	list = tokens;
	while(list)
	{
		tkn = list->content;
		if ((*list).prev == NULL)
			( tkn->type == COM_NAME);
		else if (tkn->type == TOKEN_SPACE)
			check_error(parse_space(&list));
		else if (tkn->type == TOKEN_SQUOTE)
			check_error(parser_SQ(&list));
		else if (tkn->type == TOKEN_DBQUOTE)
			check_error(parser_DBQ(&list));

	}
	return (list);
}

