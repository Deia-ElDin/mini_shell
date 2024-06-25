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

// static t_token	*is_target(t_token *target, t_token *token)
// {
// 	if (target)
// 		return (target);
// 	if ((token->type == TOKEN_WORD
// 			|| token->type == TOKEN_SINGLE_QUOTE
// 			|| token->type == TOKEN_DOUBLE_QUOTE) && token->next
// 		&& is_redirect(token->next))
// 		return (token);
// 	return (NULL);
// }

// static	bool	is_redirect_case(t_token *token)
// {
// 	if (token->prev && !token->prev->is_space)
// 		return (false);
// 	return (token->prev && token->prev->prev
// 		&& (token->type == TOKEN_WORD
// 			|| token->type == TOKEN_SINGLE_QUOTE
// 			|| token->type == TOKEN_DOUBLE_QUOTE)
// 		&& is_redirect(token->prev->prev));
// }

// static void	shift_tokens(t_token *token, t_token *target)
// {
// 	t_token	*redirect;

// 	redirect = NULL;
// 	if (is_redirect(target->next))
// 		redirect = target->next;
// 	else
// 		return ;
// 	token->prev->next = token->next;
// 	if (token->next)
// 		token->next->prev = token->prev;
// 	token->prev = target;
// 	token->next = redirect;
// 	redirect->prev = token;
// 	target->next = token;
// }

// void	token_reorder(t_data *data)
// {
// 	t_token	*token;
// 	t_token	*target;

// 	token = data->tokens;
// 	target = NULL;
// 	if (!token)
// 		return ;
// 	while (token)
// 	{
// 		target = is_target(target, token);
// 		if (token->type == TOKEN_PIPE)
// 		{
// 			if (token->next && token->next->type != TOKEN_WORD)
// 				target = token;
// 			else
// 				target = NULL;
// 		}
// 		if (target && is_redirect_case(token))
// 		{
// 			shift_tokens(token, target);
// 			target = NULL;
// 			token = data->tokens;
// 		}
// 		token = token->next;
// 	}
// }


static	bool	is_redirect_case(t_token *token)
{
	int		type;
	// if (token->prev && !token->prev->is_space)
	// 	return (false);
	if (!token->next || !token->next->next)
		return (false);
	type = token->next->next->type;
	return (type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTE
		|| type == TOKEN_DOUBLE_QUOTE);
}

static	void	shift_tokens(t_data *data, t_token *token)
{
	t_token *redirect;
	t_token *replace;

	replace = token->next->next;
	redirect = token;
	replace->prev->next = replace->next;
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
	t_token *redirect;

	token = data->tokens;
	redirect = NULL;
	if (!token)
		return ;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			redirect = NULL;
		if (is_redirect(token) && is_redirect_case(token))
		{
			shift_tokens(data, token);
			token = data->tokens;
		}
		token = token->next;
	}
}
