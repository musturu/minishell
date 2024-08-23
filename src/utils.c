#include "../minishell.h"

void	ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*current;
	t_list	*iter;

	current = *lst;
	while (current)
	{
		if (current == node)
		{
			current->prev->next = current->next;
			current->next->prev = current->prev;
			ft_lstdelone(current, del);
			return ;
		}
		current = current->next;
	}
}
