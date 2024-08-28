
#include "../minishell.h"
#include <stdio.h>

void	ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			if (!prev)
				*lst = current->next;
			if (prev)
				prev->next = current->next;
			if (current->next)
				current->next->prev = prev;
			ft_lstdelone(current, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
