
#include "../minishell.h"

char	is_after_break(t_list *tokens)
{
	token	*tkn;

	if (tokens->prev == NULL)
		return (1);
	tkn = tokens->prev->content;
	return (tkn->type == TOKEN_AND || tkn->type == TOKEN_PIPE);
}

char	is_string(TokenType type)
{
	return (type == TOKEN_WORD 
		|| type == TOKEN_SQUOTE 
		|| type == TOKEN_DBQUOTE);
}

char	is_redirection(TokenType type)
{
	return (type == TOKEN_REDIR_OUT 
		|| type == TOKEN_REDIR_IN 
		|| type == TOKEN_REDIR_PRE 
		|| type == TOKEN_REDIR_APPEND);
}
