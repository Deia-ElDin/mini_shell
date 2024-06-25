/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:15:21 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 18:40:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	empty_redirs(t_data *data)
{
	t_token	*token;
	bool	all_are_redir;

	all_are_redir = true;
	token = data->tokens;
	if (!token || !is_redirect(token))
		all_are_redir = false;
	while (token)
	{
		if (!token->next || !is_file(token->next))
			all_are_redir = false;
		if (!token->next)
			break ;
		token = token->next->next;
	}
	if (all_are_redir)
	{
		token = (t_token *)ft_calloc(1, sizeof(t_token));
		token->type = TOKEN_WORD;
		token->value = NULL;
		token->prev = NULL;
		token->next = data->tokens;
		data->tokens->prev = token;
		data->tokens = token;
	}
}

bool	lexer(t_data *data)
{
	if (!data->line)
		return (NULL);
	token_tolst(data, &data->tokens, 0);
	if (data->error)
		return (token_lstclear(data), false);
	if (!token_validation(data))
		return (token_lstclear(data), false);
	token_reorder(data);
	token_merge(data);
	empty_redirs(data);
	reset_tokens_index(data);
	return (true);
}
