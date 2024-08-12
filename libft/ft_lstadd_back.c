/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:29:33 by lmoricon          #+#    #+#             */
/*   Updated: 2024/08/12 21:46:24 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tem;

	if (!lst)
	{
		*lst = new;
		return ;
	}
	if (*lst)
	{
		tem = ft_lstlast(*(lst));
		tem -> next = new;
	}
	else
		*lst = new;
}
