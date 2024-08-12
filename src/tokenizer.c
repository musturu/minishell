/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:39 by lmoricon          #+#    #+#             */
/*   Updated: 2024/08/12 22:14:48 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

static TokenType   get_token_type(char *str)
{
    if (!*str)
        return (TOKEN_EOF);//input " "
    if (!ft_strncmp(str, "|", 1))
        return (TOKEN_PIPE);
    if (!ft_strncmp(str, ">>", 2))
        return (TOKEN_REDIR_APPEND);
    if (!ft_strncmp(str, "<<", 2))
        return (TOKEN_REDIR_PRE);
    if (!ft_strncmp(str, ">", 1))
        return (TOKEN_REDIR_IN);
    if (!ft_strncmp(str, ">", 1))
        return (TOKEN_REDIR_OUT);
    if (!ft_strncmp(str, "&", 1))
        return (TOKEN_AND);
    if (!ft_strncmp(str, "$", 1))
        return (TOKEN_DOLLAR);
    if (!ft_strncmp(str, "(", 1))
        return (TOKEN_OPEN_P);
    if (!ft_strncmp(str, ")", 1))
        return (TOKEN_CLOSE_P);
    else
        return (TOKEN_WORD);
}

static char    *get_token_value(char   *str, TokenType type)
{
    if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || type == TOKEN_AND || type == TOKEN_DOLLAR || type == TOKEN_CLOSE_P || type == TOKEN_OPEN_P)
        return (ft_substr(str, 0, 1));
    else if (type != TOKEN_WORD)
        return (ft_substr(str, 0, 2));
    else
        return (ft_substr(str, 0, space_until_next(str)));
}

static int append_token(char **str, t_list *lst)
{
    token   *tok;

    tok = calloc(1, sizeof(token));
    if (!tok)
        return (0);
    tok->type = get_token_type(*str);
    tok->value = get_token_value(*str, tok->type);
    if (!tok->value)
        return (0);
    *str += ft_strlen(tok->value);
    ft_lstadd_back(&lst, ft_lstnew(tok));
    print_list(lst);
    return (1);
}

t_list    *tokenize(char   *str, t_list  *list)
{
    if (!*str)
    {
        print_list(list);
        return (list);
    }
    go_next(&str);
    if (!append_token(&str, list))
        return (NULL);
    return (tokenize(str, list));
}