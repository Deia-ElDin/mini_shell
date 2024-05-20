/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:42:35 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 20:54:43 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_token_mergeable(t_token *token);
static char	*remove_quotes(t_data *data, t_token *token);
static char	*merge_values(t_data *data, t_token *first, t_token *second);
static void	new_token(t_data *data, t_token *first, t_token *second);
void		token_merge(t_data *data);

static bool	is_token_mergeable(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == CMD)
		return (true);
	if (token->type == SINGLE_QUOTE)
		return (true);
	if (token->type == DOUBLE_QUOTE)
		return (true);
	return (false);
}

static char	*remove_quotes(t_data *data, t_token *token)
{
	char	*new;
	size_t	len;

	if (!token)
		return (NULL);
	if (token->type != SINGLE_QUOTE && token->type != DOUBLE_QUOTE)
		return (token->value);
	len = ft_strlen(token->value);
	if (len < 2)
		return (token->value);
	new = NULL;
	new = ft_substr(token->value, 1, len - 2);
	if (!new)
		exit_failure(data);
	return (new);
}

static char	*merge_values(t_data *data, t_token *first, t_token *second)
{
	char	*merged;
	char	*first_value;
	char	*second_value;

	first_value = remove_quotes(data, first);
	second_value = remove_quotes(data, second);
	merged = NULL;
	if (first->is_space)
		merged = ft_strnjoin(3, first_value, " ", second_value);
	else
		merged = ft_strjoin(first_value, second_value);
	if (!merged)
		exit_failure(data);
	return (merged);
}

static void	new_token(t_data *data, t_token *first, t_token *second)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_failure(data);
	token->type = CMD;
	token->value = merge_values(data, first, second);
	token->is_space = false;
	token->prev = NULL;
	token->next = NULL;
	if (second->is_space)
		token->is_space = true;
	if (first->prev)
	{
		first->prev->next = token;
		token->prev = first->prev;
	}
	else
		data->tokens = token;
	if (second->next)
	{
		second->next->prev = token;
		token->next = second->next;
	}
	(token_delone(&first), token_delone(&second));
}

void	token_merge(t_data *data)
{
	t_token	*token;
	t_token	*next;

	token = data->tokens;
	while (token && token->next)
	{
		token->index = 0;
		next = token->next;
		if (is_token_mergeable(token) && is_token_mergeable(next))
		{
			new_token(data, token, next);
			token = data->tokens;
		}
		else
			token = token->next;
	}
	token = data->tokens;
	while (token)
	{
		if (!token->prev)
			token->index = 0;
		else
			token->index = token->prev->index + 1;
		token = token->next;
	}
}
