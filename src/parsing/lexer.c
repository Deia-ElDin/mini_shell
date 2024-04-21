/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 13:29:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// bool	validate_tokens(t_data *data, t_token *head)
// {
// 	t_token	*current;

// 	current = head;
// 	while (current)
// 	{
// 		if (current->type == TOKEN_PIPE)
// 		{
// 			if (!current->next || current->next->type == TOKEN_PIPE)
// 			{
// 				error_msg("syntax error near unexpected token `|'", data);
// 				return (false);
// 			}
// 		}
// 		else if (current->type == TOKEN_REDIR)
// 		{
// 			if (!current->next || current->next->type == TOKEN_REDIR)
// 			{
// 				error_msg("syntax error near unexpected token `newline'", data);
// 				return (false);
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return (true);
// }
/**
 * The purpose of this function is to create the tokens
 * then it returns the head of the created list
*/

bool	lexer(t_data *data)
{
	t_token	*head;

	head = NULL;
	if (!data->line)
		return (NULL);
	token_tolst(data, &data->tokens, 0);
	return (token_validation(data));
}
