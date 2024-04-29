/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:59:20 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 11:26:51 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_special_token(t_token *token)
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

bool	is_pre(t_token *token)
{
	int	crnt_index;
	int	next_index;

	if (!token || !token->next)
		return (false);
	crnt_index = token->index;
	next_index = token->next->index;
	return (crnt_index < next_index && next_index - crnt_index == 1);
}

bool	is_post(t_token *token)
{
	int	crnt_index;
	int	prev_index;

	if (!token || !token->prev)
		return (false);
	crnt_index = token->index;
	prev_index = token->prev->index;
	return (crnt_index > prev_index && crnt_index - prev_index == 1);
}
