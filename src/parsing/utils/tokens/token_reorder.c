/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:34:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 17:10:52 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_redirect_case(t_token *token)
{
	int		type;

	if (!token->next || !token->next->next)
		return (false);
	type = token->next->next->type;
	return (token->next->is_space
		&& (type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTE
			|| type == TOKEN_DOUBLE_QUOTE));
}

static	void	shift_tokens(t_data *data, t_token *token)
{
	t_token	*redirect;
	t_token	*replace;

	replace = token->next->next;
	redirect = token;
	replace->prev->next = replace->next;
	if (replace->next)
		replace->next->prev = replace->prev;
	if (redirect->prev)
		redirect->prev->next = replace;
	replace->prev = redirect->prev;
	replace->next = redirect;
	redirect->prev = replace;
	if (data->tokens == redirect)
		data->tokens = replace;
}

void	token_reorder(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	if (!token)
		return ;
	while (token)
	{
		if (is_redirect(token) && is_redirect_case(token))
		{
			shift_tokens(data, token);
			token = data->tokens;
		}
		token = token->next;
	}
}
