/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:42:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 16:37:36 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

static bool	valid_pipe(t_token *crnt);
static bool	valid_redirect(t_token *crnt);
bool		token_validation(t_data *data);

/// @brief Used to validate the pipes with the prev and next tokens
/// @param crnt Current token
/// @return True or false depends if the test pass or not
static bool	valid_pipe(t_token *crnt)
{
	if (!crnt->prev || crnt->prev->type == TOKEN_PIPE)
		return (false);
	if (!crnt->next || crnt->next->type == TOKEN_PIPE)
		return (false);
	return (true);
}

/// @brief Used to validate the redirects with the next token
/// @param crnt Current token
/// @return True or false depends if the test pass or not
static bool	valid_redirect(t_token *crnt)
{
	if (!crnt->next)
		return (false);
	if (crnt->next->type != TOKEN_WORD && crnt->next->type != TOKEN_SINGLE_QUOTE
		&& crnt->next->type != TOKEN_DOUBLE_QUOTE)
		return (false);
	return (true);
}

/// @brief Used to validate the tokens
/// @param data The main struct
/// @return True or false
bool	token_validation(t_data *data)
{
	t_token	*crnt;

	crnt = data->tokens;
	while (crnt)
	{
		if (crnt->type == TOKEN_PIPE && !valid_pipe(crnt))
			return (syntax_error(data, crnt->value), false);
		else if ((crnt->type == TOKEN_REDIR_IN
				|| crnt->type == TOKEN_REDIR_OUT
				|| crnt->type == TOKEN_APPEND
				|| crnt->type == TOKEN_HEREDOC)
			&& !valid_redirect(crnt))
			return (syntax_error(data, crnt->value), false);
		crnt = crnt->next;
	}
	return (true);
}
