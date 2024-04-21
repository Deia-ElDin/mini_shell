/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:42:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 20:19:39 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * The purpose of this function is to validate the pipes
 * we check if the previous and the next token are not pipes
 * if they are we return false
 * else we return true
*/

static bool	valid_pipe(t_token *crnt)
{
	if (!crnt->prev || crnt->prev->type == TOKEN_PIPE)
		return (false);
	if (!crnt->next || crnt->next->type == TOKEN_PIPE)
		return (false);
	return (true);
}

/**
 * The purpose of this function is to validate the redirects
 * we check if the next token is a redirect of any type or a pipe
 * if it is we return false
 * else we return true
*/

static bool	valid_redirect(t_token *crnt)
{
	if (!crnt->next)
		return (false);
	if (crnt->next->type >= TOKEN_REDIR_IN && crnt->next->type <= TOKEN_PIPE)
		return (false);
	return (true);
}

/**
 * The purpose of this function is to validate the tokens
 * we validate the pipes and the redirects
*/

bool	token_validation(t_data *data)
{
	t_token	*crnt;

	crnt = data->tokens;
	while (crnt)
	{
		if (crnt->type == TOKEN_PIPE && !valid_pipe(crnt))
			return (syntax_error(crnt->value), false);
		else if ((crnt->type == TOKEN_REDIR_IN
				|| crnt->type == TOKEN_REDIR_OUT
				|| crnt->type == TOKEN_APPEND
				|| crnt->type == TOKEN_HEREDOC)
			&& !valid_redirect(crnt))
			return (syntax_error(crnt->value), false);
		crnt = crnt->next;
	}
	return (true);
}
