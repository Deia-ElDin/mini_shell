/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:49:47 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 18:25:47 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * The purpose of this function is to create a new token
 * if the line is empty or the len is 0 we return NULL (protections)
 * we get the value of the token by using ft_substr
 * we make sure it's not an empty string ("   "), ("")
 * if it's an empty string, we free the value and return NULL
 * we set the token value by trimming the value (cleaning the whitespaces)
*/

t_token	*token_new(t_data *data, unsigned int start, int len)
{
	t_token	*token;
	char	*value;

	if (!data->line || !len)
		return (NULL);
	value = ft_substr(data->line, start, (size_t)len);
	if (!value)
		exit_failure(data);
	if (ft_isempty_str(value))
		return (ft_free(&value, 'p'), NULL);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_failure(data);
	token->type = token_type(value);
	if (ft_strchr(value, '$')
		&& (token->type == TOKEN_WORD || token->type == TOKEN_DOUBLE_QUOTE))
		token->value = env_expansion(data, value);
	else
		token->value = ft_strtrim(value, WHITESPACES);
	token->prev = NULL;
	token->next = NULL;
	ft_free(&value, 'p');
	if (!token->value)
		exit_failure(data);
	return (token);
}
