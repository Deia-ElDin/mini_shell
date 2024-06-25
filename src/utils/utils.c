/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:59:45 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 17:11:10 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token *token)
{
	return (token->type >= TOKEN_REDIR_IN && token->type <= TOKEN_HEREDOC);
}

bool	is_quotes(t_token *token)
{
	return (token->type == TOKEN_SINGLE_QUOTE
		|| token->type == TOKEN_DOUBLE_QUOTE);
}

bool	is_token_mergeable(t_token *token)
{
	if (!token)
		return (false);
	if (token->prev && token->next && token->type == TOKEN_WORD
		&& token->prev->type >= TOKEN_REDIR_IN
		&& token->prev->type <= TOKEN_HEREDOC
		&& token->next->type == TOKEN_WORD)
		return (false);
	if (token->type == TOKEN_WORD)
		return (true);
	if (token->type == TOKEN_SINGLE_QUOTE)
		return (true);
	if (token->type == TOKEN_DOUBLE_QUOTE)
		return (true);
	return (false);
}

void	reset_tokens_index(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (!token->prev)
			token->index = 0;
		else
			token->index = token->prev->index + 1;
		token = token->next;
	}
}

void	set_data_init_null(t_data *data)
{
	data->curr_pid = 0;
	data->cmd_count = 0;
	data->pids = NULL;
	data->line = NULL;
	data->env_list = NULL;
	data->env = NULL;
	data->env_arr = NULL;
	data->env_arr = NULL;
	data->path = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	data->error = false;
	data->exit_status = 0;
}
