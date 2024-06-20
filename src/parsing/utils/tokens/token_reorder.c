/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:34:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 19:23:36 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	void	check_redirects(t_token *token)
// {
// 	t_token	*next;

// 	if (!token->prev || !token->next)
// 		return ;
// 	next = token->next;
// 	if (!next || !next->next)
// 		return ;
// 	if (next->next->type == TOKEN_WORD)
// }

static t_token	*is_target(t_token *token)
{
	if (token->type == TOKEN_WORD && token->next && is_redirect(token->next))
		return (token);
	return (NULL);
}

void	token_reorder(t_data *data)
{
	t_token	*token;
	t_token	*target;

	token = data->tokens;
	if (!token)
		return ;
	while (token)
	{
		target = is_target(token);
		if (target && token->type == TOKEN_WORD
			&& token->prev && is_file(token->prev))
		{
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = target;
			token->next = target->next;
			target->next->prev = token;
			target->next = token;
			target = NULL;
		}
		token = token->next;
	}
}
