/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:42:35 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 17:09:36 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(t_data *data, t_token *token)
{
	char	*new;
	size_t	len;

	if (!token)
		return (NULL);
	if (token->type != TOKEN_SINGLE_QUOTE && token->type != TOKEN_DOUBLE_QUOTE)
		return (token->value);
	len = ft_strlen(token->value);
	if (len < 2)
		return (token->value);
	new = ft_substr(token->value, 1, len - 2);
	if (!new)
		return (data_status(data, 1), token->value);
	return (new);
}

static	void	handle_remove_qoutes(t_data *data, t_token *token)

{
	char	*old_value;

	old_value = token->value;
	token->value = remove_quotes(data, token);
	token->type = TOKEN_WORD;
	free(old_value);
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
	if (first_value && first_value != first->value)
		ft_free(&first_value, 'p');
	if (second_value && second_value != second->value)
		ft_free(&second_value, 'p');
	if (!merged)
		return (data_status(data, 1), NULL);
	return (merged);
}

static void	new_token(t_data *data, t_token *first, t_token *second)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (data_status(data, 1));
	token->type = TOKEN_WORD;
	token->value = merge_values(data, first, second);
	token->is_space = false;
	token->prev = NULL;
	token->next = NULL;
	if (second && second->is_space)
		token->is_space = true;
	if (first->prev)
	{
		first->prev->next = token;
		token->prev = first->prev;
	}
	else
		data->tokens = token;
	if (second && second->next)
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
	while (token)
	{
		token->index = 0;
		next = token->next;
		if (is_token_mergeable(token) && is_token_mergeable(next))
		{
			new_token(data, token, next);
			token = data->tokens;
		}
		else if (is_quotes(token))
			handle_remove_qoutes(data, token);
		else
			token = token->next;
	}
	reset_tokens_index(data);
}
