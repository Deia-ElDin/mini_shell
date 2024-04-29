/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 07:56:45 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 19:46:00 by dehamad          ###   ########.fr       */
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

static	t_token	*token_next_special(t_token *token)
{
	t_token	*next;

	next = NULL;
	if (!token)
		return (NULL);
	while (token)
	{
		if (is_special_token(token))
		{
			next = token;
			break ;
		}
		token = token->next;
	}
	if (!next)
		return (NULL);
	if (next->index - token->index <= 2)
		return (next);
	return (NULL);
}

// static	t_token	*token_last_match(t_token *token)
// {
// 	t_token	*last;

// 	last = NULL;
// 	while (token)
// 	{
// 		if (!last && is_special_token(token))
// 			last = token;
// 		else if (last && last->type == token->type)
// 			last = token;
// 		else if (last && last->type != token->type)
// 			return (last);
// 		token = token->next;
// 	}
// 	return (last);
// }

static t_token	*token_get(t_ast *head)
{
	t_token	*token;

	token = head->token->next;
	if (head->type == TOKEN_AND || head->type == TOKEN_OR
		|| head->type == TOKEN_WORD)
		return (token_next_special(token));
	else if (head->type == TOKEN_PIPE && token->type == TOKEN_WORD)
		return (token);
	return (token);
}

t_ast	*ast_right(t_data *data, t_ast *head)
{
	if (!head)
		return (NULL);
	return (ast_new(data, token_get(head)));
}

// static t_token	*token_get(t_ast *head)
// {
// 	t_token	*token;
// 	t_token	*match;

// 	match = NULL;
// 	token = head->token->next;
// 	while (token)
// 	{
// 		if (is_special_token(token))
// 			match = token;
// 		if (match)
// 		{
// 			if (match->type == token->type)
// 				match = token;
// 			else
// 				return (match);
// 		}
// 		token = token->next;
// 	}
// 	return (match);
// }

// static	bool	is_redirect(t_token *token)
// {
// 	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
// 		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC);
// }

// static	bool	is_special_token(t_token *token)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == TOKEN_AND || token->type == TOKEN_OR
// 		|| token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
// 		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC
// 		|| token->type == TOKEN_PIPE)
// 		return (true);
// 	return (false);
// }

// static	bool	is_word_token(t_token *token)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == TOKEN_WORD)
// 		return (true);
// 	return (false);
// }

// static t_token	*token_get(t_data *data, t_ast *head)
// {
// 	t_token	*token;
// 	t_token	*match;

// 	token = head->token;
// 	match = NULL;
// 	while (token)
// 	{
// 		if (token->index != head->token->index)
// 		{
// 			if (token->type == data->highest_token)
// 			{
// 				match = token;
// 				if (token->type == head->token->type)
// 					return (match);
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (match);
// }
// static t_token	*token_get(t_data *data, t_ast *head)
// {
// 	t_token	*token;
// 	t_token	*match;

// 	(void)data;
// 	token = head->token;
// 	match = NULL;
// 	while (token)
// 	{
// 		if (token->index != head->token->index)
// 		{
// 			if (is_special_token(token))
// 				match = token;
// 			if (match)
// 			{
// 				if (match->type == token->type)
// 					match = token;
// 				else
// 					return (match);
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (match);
// }

// t_ast	*ast_right(t_data *data, t_ast *head)
// {
// 	t_token	*token;

// 	token = NULL;
// 	data->highest_token = data->highest_token;
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
	// {
	// 	token = head->token;
	// 	if (is_word_token(token))
	// 		return (NULL);
	// 	// else if (token->next && is_special_token(token)
	// 	// 	&& is_word_token(token->next)
	// 	// 	&& !token->next->is_taken)
	// 	// 	return (ast_new(data, token->next));
	// }
	// if (is_redirect(head->token))
	// 	return (ast_new(data, head->token->next));