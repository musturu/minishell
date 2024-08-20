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

// static int check_error(int i)
// {
// 	if (i == 0)
// 	{
// 		printf("Error");
// 		return (1);
// 	}
// 	return (0);
// }


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


t_list	*parser(t_list *tokens)
{
	token   *tkn;
	t_list	*list;
	t_list	*ret;
	cmd		*comd;

	ret = NULL;
	list = tokens;
	while(list->next)
	{
		tkn = list->content;
		comd = new_cmd(&list);
		ft_lstadd_back(&ret, ft_lstnew(comd));
		list = list->next;
	}
	return (ret);
}

