/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:58:31 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/26 14:33:20 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_type(t_token *token, char *value)
{
	token->is_quotes = 0;
	if (*value == '\'' && ++token->is_quotes)
		return (TOKEN_SINGLE_QUOTE);
	if (*value == '\"' && ++token->is_quotes)
		return (TOKEN_DOUBLE_QUOTE);
	if (!ft_strcmp(value, "&&"))
		return (TOKEN_AND);
	if (!ft_strcmp(value, "||"))
		return (TOKEN_OR);
	if (!ft_strcmp(value, "<<"))
		return (TOKEN_HEREDOC);
	if (!ft_strcmp(value, ">>"))
		return (TOKEN_APPEND);
	if (!ft_strcmp(value, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(value, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(value, "|"))
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

static t_token	*token_values(t_data *data, char *value, int index)
{
	t_token	*token;
	char	*dollar_sign;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (data_status(data, 1), NULL);
	token->type = token_type(token, value);
	dollar_sign = ft_strchr(value, '$');
	if (dollar_sign && *(dollar_sign + 1) != '"' && *(dollar_sign + 1) != ' '
		&& token->type != TOKEN_SINGLE_QUOTE && ft_strlen(value) > 1)
		token->value = env_expansion(data, value);
	else
		token->value = ft_strtrim(value, WHITESPACES);
	if (!token->value)
		return (free(token), NULL);
	if (data->line[index] == ' ')
		token->is_space = true;
	else
		token->is_space = false;
	token->is_parsed = false;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

static t_token	*token_new(t_data *data, int start, int len)
{
	char	*value;
	t_token	*new;

	if (!data->line || !len)
		return (NULL);
	value = ft_substr(data->line, start, (size_t)len);
	if (!value)
		return (data_status(data, 1), NULL);
	if (ft_isempty_str(value))
		return (ft_free(&value, 'p'), NULL);
	new = token_values(data, value, start + len);
	ft_free(&value, 'p');
	if (!new)
		return (NULL);
	return (new);
}

void	token_add(t_data *data, t_token **head, int start, int len)
{
	t_token	*token;
	t_token	*tmp;

	token = token_new(data, start, len);
	if (!token)
		return ;
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!*head)
	{
		token->index = 0;
		*head = token;
	}
	else
	{
		token->index = tmp->index + 1;
		tmp->next = token;
		token->prev = tmp;
	}
}
