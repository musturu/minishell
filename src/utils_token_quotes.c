#include "../minishell.h"
#include <stdio.h>

int	count_quotes(char *str, char quote)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == quote)
			ret++;
		i++;
	}
	if (ret % 2 == 1)
		return (0);
	else
		return (1);
}

char	*expand(char *str, char **env, char c)
{

	return (ret);
}


char	*dquote_manager(char *str, char **env)
{
	int		i;
	char	*first;
	char	*ret;
	char	*second;

	i = 1;
	if (!count_quotes(str, '\"'))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"')
			break ;
		i++;
	}
	first = (ft_substr(str, 1, i - 1));
	if (ft_strchr(first, '$'))
		first = expand(str, env, '$');
	str += i + 1;
	while (!ft_isspace(str[i]))
		i++;
	second = ft_substr(str, 0, i - 1);
	ret = ft_strjoin(first, second);
	free(first);
	free(second);
	return (ret);
}
char	*squote_manager(char *str)
{
	int		i;
	char	*first;
	char	*ret;
	char	*second;

	i = 1;
	if (!count_quotes(str, '\''))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			break ;
		i++;
	}
	first = (ft_substr(str, 1, i - 1));
	str += i + 1;
	while (!ft_isspace(str[i]))
		i++;
	second = ft_substr(str, 0, i - 1);
	ret = ft_strjoin(first, second);
	free(first);
	free(second);
	return (ret);
}
