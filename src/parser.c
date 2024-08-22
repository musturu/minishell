/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:52:52 by mamerlin          #+#    #+#             */
/*   Updated: 2024/08/20 19:07:07 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>


cmd	*new_cmd(t_list **tokens)
{
	cmd	*new;
	token *tkn;
	token *tknnext;

	new = malloc(sizeof(cmd));
	if (!new)
		return (NULL);
	tkn = (*tokens)->content;
	tknnext = (*tokens)->next->content;
	new->args = NULL;
	if ((*tokens)->prev == NULL && (tkn->type == TOKEN_WORD || tkn->type == TOKEN_DBQUOTE || tkn->type == TOKEN_SQUOTE)) //da aggiuungere nella prima condizione che oltre ad essere il primo potrebbe anche essre subito dopo un tokken NON-WORD
	{
		new->cmd = tkn->value;
		while (tknnext->type == TOKEN_WORD || tknnext->type == TOKEN_DBQUOTE || tknnext->type == TOKEN_SQUOTE)
		{
			ft_lstadd_back(&new->args, ft_lstnew(tknnext->value));
			(*tokens) = (*tokens)->next;
			tknnext = (*tokens)->next->content;
		}
	} // ew
	tkn = (*tokens)->content;
	if (tkn->type == TOKEN_REDIR_OUT)
		new->outpath = tkn->value;
	new->inpath = NULL;
	new->outfd = 1;
	new->infd = 0;
	return (new);
}

static char	*get_command_command(t_list **tokens)
{
	token	*tkn;

	tkn = (*tokens)->content;
	if (is_after_break(*tokens) //da aggiuungere su is_after_break che prev  puo essere is_string se prev.prev == is_redirection
		&& (is_string(tkn->type) || is_redirection(tkn->type)))  
	{
		*tokens = (*tokens)->next;
		return (tkn->value);
	}
	else
		return (NULL);
}


static t_list	*get_command_args(t_list **tokens)
{
	t_list	*ret;
	token	*tknnext;

	ret = NULL;
	tknnext = (*tokens)->content;
	while (is_string(tknnext->type))
	{
		ft_lstadd_back(&ret, ft_lstnew(tknnext->value));
		(*tokens) = (*tokens)->next;
		tknnext = (*tokens)->content;
	}
	return (ret);
}

static char	*get_command_in(t_list **tokens)
{
	token	*tkn;

	tkn = (*tokens)->content;
	if ((tkn->type == TOKEN_REDIR_IN || tkn->type == TOKEN_REDIR_PRE) && (*tokens)->next)
	{
		*tokens = (*tokens)->next;
		tkn = (*tokens)->content;
		if (is_string(tkn->type))
		{
			*tokens = (*tokens)->next;
			return (tkn->value);
		}

	}
	else if (tkn->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		return (tkn->value);
	}
	return (NULL);
}

static char	*get_command_out(t_list **tokens)
{
	token	*tkn;

	tkn = (*tokens)->content;
		printf("entra\n %i", tkn->type);
	if ((tkn->type == TOKEN_REDIR_OUT || tkn->type == TOKEN_REDIR_APPEND) && (*tokens)->next)
	{
		*tokens = (*tokens)->next;
		tkn = (*tokens)->content;
		if (is_string(tkn->type))
		{
			*tokens = (*tokens)->next;
			return (tkn->value);
		}

	}
	else if (tkn->type == TOKEN_PIPE)
		return (tkn->value);
	else if (tkn->type == TOKEN_AND || tkn->type == TOKEN_EOF)
	{
		*tokens = (*tokens)->next;
		return (tkn->value);
	}
	return (NULL);
}

static int	append_cmd(t_list	**tokens, t_list **parsed_list)
{
	cmd	*command;

	command = ft_calloc(1, sizeof(cmd));
	if (!command)
		return (0);
	command->inpath = get_command_in(tokens);
	command->cmd = get_command_command(tokens);
	command->args = get_command_args(tokens);
	command->outpath = get_command_out(tokens);
	printf("wtf%s\n", command->cmd);
	ft_lstadd_back(parsed_list, ft_lstnew(command));
	return (1);
}

t_list	*parser2(t_list **tokens,t_list **parsed_list)
{
	if (!*tokens || ((token *)(*tokens)->content)->type == TOKEN_EOF)
		return (*parsed_list);
	if (!append_cmd(tokens, parsed_list))
		return (NULL);
	return (parser2(tokens, parsed_list));
}

t_list	*parser(t_list *tokens)
{
	t_list	*list;
	t_list	*ret;
	cmd		*comd;

	ret = NULL;
	list = tokens;
	while(list->next)
	{
		comd = new_cmd(&list);
		ft_lstadd_back(&ret, ft_lstnew(comd));
		list = list->next;
	}
	return (ret);
}

