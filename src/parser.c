/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:52:52 by mamerlin          #+#    #+#             */
/*   Updated: 2024/08/13 17:06:33 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int parser_word(t_list **list)
{
	if (list.)
}

t_list	*parser(t_list *tokens)
{
	t_list	*list;

	list = tokens;
	while(list)
	{
		if(list->content == TOKEN_WORD)
			parser_word(&list);
		else
			list = list->next;
	}
	return (list);
}
