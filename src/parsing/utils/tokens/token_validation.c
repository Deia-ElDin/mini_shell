/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:42:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 15:07:09 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../../includes/minishell.h"

static bool	valid_pipe(t_token *crnt)
{
	if (!crnt->prev || crnt->prev->type == TOKEN_PIPE)
		return (false);
	if (!crnt->next || crnt->next->type == TOKEN_PIPE)
		return (false);
	return (true);
}

static bool	valid_redirect(t_token *crnt)
{
	if (!crnt->next)
		return (false);
	if (crnt->next->type >= TOKEN_REDIR_IN && crnt->next->type <= TOKEN_PIPE)
		return (false);
	return (true);
}

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
