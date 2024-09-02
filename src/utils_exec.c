#include "../minishell.h"
#include <stdio.h>

char	is_builtin(char *cmd)
{
	int	len;

	return (0);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	//add others
	return (0);
}

char **listomap(t_list **list)
{
	int i;
	int size;


	printf("%s", (char *)(*list)->content);
	i = 0;
	char **mat;
	size = ft_lstsize(*list);
	printf("%d  LSIRASHRJASd\n", size);
	mat = (char **)malloc(sizeof(char *) * (size + 1));

	while ((*list)->next)
	{
		mat[i] = ft_strdup((*list)->content);
		printf("%s\n", mat[i]);
		i++;
		*list = (*list)->next;
	}
	mat[i] = NULL;
	ft_lstclear(list, free);
	return (mat);
}
