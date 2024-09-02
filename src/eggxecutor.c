#include "../minishell.h"
#include <stdio.h>

static int	redir_out(command *cmd)
{
	if (cmd->outpath)
	{
		if (cmd->outpath[1] == '>')
		{
			if (access(cmd->outpath + 2, W_OK) == 0)
				cmd->outfd = open(cmd->inpath + 2, O_APPEND | O_CREAT, NULL);
			else
				return (0);
		}
		else
			if (access(cmd->outpath + 1, W_OK) == 0) 
				cmd->infd = open(cmd->inpath + 1, O_WRONLY | O_CREAT);
			else
				return (0);
	}
	return (1);
}

static int	redir_in(command *cmd)
{
	if (cmd->inpath)
	{
		if (cmd->inpath[1] == '<') //da implementare << 
		{
		if (access(cmd->inpath + 2, R_OK) == 0)
				cmd->infd = open(cmd->outpath + 2, O_RDONLY);
		else
			return (0);
		}
		else
		{
			if (access(cmd->outpath + 1, R_OK) == 0)
				cmd->infd = open(cmd->inpath + 1, O_RDONLY);
			else
				return (0);
		}
	}
	return (1);
}


char	*get_path(char **env, char *command)
{
	char	**paths;
	char	*ret;
	int		i;

	i = 0;
	command = ft_strjoin("/", command);
	paths = ft_split(env[str_to_env_index(env, "PATH")], ':');
	ret	= ft_strjoin(*paths, command);
	while (paths[i] && access(ret, X_OK) != 0)
	{
		free(ret);
		ret	= ft_strjoin(paths[i], command);
		i++;
	}
	free(command);
	if (paths[i])
	{
		free_matrix(paths);
		return (ret);
	}
	free(ret);
	return (NULL);
}

int	execute(t_list **parsed_list, char **env)
{
	command	*cur;
	command	*next;
	int		piped[2];
	pid_t	pid;

	if (!(*parsed_list))
		return (1);
	cur = (*parsed_list)->content;
	if ((*parsed_list)->next)
		next = (*parsed_list)->next->content;
	if (cur->outconnect == TOKEN_PIPE)
	{
		if (pipe(piped) == -1)
			return (0);
		next->infd = piped[0];
		cur->outfd = piped[1];
	}
	pid = fork();
	cur->argv = NULL;
	if (!pid)
	{
		redir_in(cur); //add guard
		redir_out(cur); //add guard
		if (cur->infd != STDIN_FILENO)
			dup2(STDIN_FILENO, cur->infd); //add dup2 guard
		if (cur->outfd != STDOUT_FILENO)
			dup2(STDOUT_FILENO, cur->outfd); //add dup2 guard
		if (is_builtin(cur->cmd))
			printf("BUILTIN!\n");
		else
		{
			printf("%i,%i!%s\n", cur->outfd, cur->infd, get_path(env, cur->cmd));
			execve(get_path(env, cur->cmd),cur->argv, env); //spostare su un altra funzione a mettere get_path e argv su cmd cosi possono essere freeati
		}
	}
	if (cur->outconnect != TOKEN_AND)
		waitpid(pid, NULL, 0); //we can use the second parameter to store exit status of process. man waitpid
	execute(&(*parsed_list)->next, env);
	return 1;
}
