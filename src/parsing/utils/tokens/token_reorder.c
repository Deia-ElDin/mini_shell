/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:34:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 19:58:26 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*is_target(t_token *target, t_token *token)
{
	if (target)
		return (target);
	if ((token->type == TOKEN_WORD || token->type == TOKEN_SINGLE_QUOTE
		|| token->type == TOKEN_DOUBLE_QUOTE) && token->next
		&& is_redirect(token->next))
		return (token);
	return (NULL);
}

static	bool	is_redirect_case(t_token *token)
{
	if (token->prev && !token->prev->is_space)
		return (false);
	return (token->prev && token->prev->prev
		&& (token->type == TOKEN_WORD || token->type == TOKEN_SINGLE_QUOTE
		|| token->type == TOKEN_DOUBLE_QUOTE)
		&& is_redirect(token->prev->prev));
}

static void	shift_tokens(t_token *token, t_token *target)
{
	t_token	*redirect;

	redirect = token->prev->prev;
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = target;
	token->next = redirect;
	redirect->prev = token;
	target->next = token;
}

void	token_reorder(t_data *data)
{
	t_token	*token;
	t_token	*target;

	token = data->tokens;
	target = NULL;
	if (!token)
		return ;
	while (token)
	{
		target = is_target(target, token);
		if (is_redirect_case(token))
		{
			shift_tokens(token, target);
			target = NULL;
			token = data->tokens;
		}
		token = token->next;
	}
}
