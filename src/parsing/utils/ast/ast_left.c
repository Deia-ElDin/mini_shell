/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_left.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 07:46:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 18:22:09 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static	bool	is_special_token(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_AND || token->type == TOKEN_OR
		|| token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_PIPE)
		return (true);
	return (false);
}

static	t_token	*token_prev_special(t_token *token)
{
	t_token	*prev;

	prev = NULL;
	if (!token)
		return (NULL);
	while (token)
	{
		if (is_special_token(token))
		{
			prev = token;
			break ;
		}
		token = token->prev;
	}
	if (!prev)
		return (NULL);
	if (token->index - prev->index <= 2)
		return (prev);
	return (NULL);
}

// static	t_token	*token_prev_word(t_token *token)
// {
// 	while (token)
// 	{
// 		if (token->type == TOKEN_WORD)
// 			return (token);
// 		token = token->prev;
// 	}
// 	return (NULL);
// }

static t_token	*token_get(t_ast *head)
{
	t_token	*token;

	token = head->token->prev;
	if (head->type == TOKEN_AND || head->type == TOKEN_OR
		|| head->type == TOKEN_WORD)
		return (token_prev_special(token));
	// else if (head->type == TOKEN_PIPE && token->type == TOKEN_WORD)
	// 	return (token);
	return (token);
}

t_ast	*ast_left(t_data *data, t_ast *head)
{
	if (!head)
		return (NULL);
	return (ast_new(data, token_get(head)));
}

// static	bool	is_same_type(t_token *token, int type)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == type)
// 		return (true);
// 	return (false);
// }

// static	bool	is_match(t_data *data, t_token *token)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == data->highest_token)
// 		return (true);
// 	return (false);
// }

// static	t_token	*token_prev_special(t_token *token)
// {
// 	while (token)
// 	{
// 		if (is_special_token(token))
// 			return (token);
// 		token = token->prev;
// 	}
// 	return (NULL);
// }

// if (!token->is_taken && token->type == data->highest_token)
// {
// 	token->is_taken = true;
// 	return (token);
// }

// t_ast	*ast_left(t_data *data, t_ast *head)
// {
// 	t_token	*token;

// 	token = NULL;
// 	while (data->highest_token >= 3)
// 	{
// 		token = token_get(data, head);
// 		if (token)
// 			break ;
// 		data->highest_token--;
// 	}
// 	return (ast_new(data, token));
// }
	// if (head)
		// data->highest_token = head->token->type;
	// if (head && head->token->type == TOKEN_WORD)
	// 	return (NULL);
	// if (head)
	// {
	// 	token = head->token;
	// 	if (is_word_token(token))
	// 		return (NULL);
	// 	// else if (token->prev && is_special_token(token)
	// 	// 	&& is_word_token(token->prev)
	// 	// 	&& !token->prev->is_taken)
	// 	// 	return (ast_new(data, token->prev));
	// }