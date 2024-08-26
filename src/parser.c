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


/*
 * the parser functions in the same exact way the tokenizer does, by calling itself it attaches
 * at the end of the list a new node, consuming the utilized token nodes in the process.
 *
 */

command	*new_cmd(t_list **tokens)
{
	command	*new;
	token *tkn;
	token *tknnext;

	new = malloc(sizeof(command));
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
	char	*ret;

	tkn = (*tokens)->content;
	if (is_after_break(*tokens)
		&& (is_string(tkn->type) || is_redirection(tkn->type)))  
	{
		ret = ft_strdup(tkn->value);
		ft_lst_remove_node(tokens, *tokens, free_token);
		return (ret);
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
		ft_lst_remove_node(tokens, *tokens, free_token);
		/*(*tokens) = (*tokens)->next;*/
		tknnext = (*tokens)->content;
	}
	return (ret);
}

static char	*get_command_in(t_list **tokens)
{
	t_list	*lst;
	char	*ret;

	lst = *tokens;
	while (lst && !is_break(lst))
	{
		if ((((token *)(lst->content))->type == TOKEN_REDIR_IN || ((token *)(lst->content))->type == TOKEN_REDIR_PRE) && lst->next)
		{
			lst = lst->next;
			if (is_string(((token *)(lst->content))->type))
			{
				ret = ft_strjoin(((token *)(lst->prev->content))->value, ((token *)(lst->content))->value);
				ft_lst_remove_node(tokens, lst->prev, free_token);
				ft_lst_remove_node(tokens, lst, free_token);
				return (ret);
			}
		}
		lst = lst->next;
	}
	return (NULL);
}

static char	*get_command_out(t_list **tokens)
{
	t_list	*lst;
	char	*ret;

	lst = *tokens;
	while (lst && !is_break(lst))
	{
		if ((((token *)(lst->content))->type == TOKEN_REDIR_OUT || ((token *)(lst->content))->type == TOKEN_REDIR_APPEND) && (*tokens)->next)
		{
			lst = lst->next;
			if (is_string(((token *)(lst->content))->type))
			{
				ret = ft_strjoin(((token *)(lst->prev->content))->value, ((token *)(lst->content))->value);
				ft_lst_remove_node(tokens, lst->prev, free_token);
				ft_lst_remove_node(tokens, lst, free_token);
				return (ret);
			}
		}
		lst = lst->next;
	}
	return (NULL);
}

static int	append_cmd(t_list	**tokens, t_list **parsed_list)
{
	command	*cmd;

	cmd = ft_calloc(1, sizeof(command));
	if (!cmd)
		return (0);
	cmd->inpath = get_command_in(tokens);
	cmd->outpath = get_command_out(tokens);
	cmd->cmd = get_command_command(tokens);
	cmd->args = get_command_args(tokens);
	ft_lstadd_back(parsed_list, ft_lstnew(cmd));
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
	command		*comd;

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

