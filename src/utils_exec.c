#include "../minishell.h"

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
