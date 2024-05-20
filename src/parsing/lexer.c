/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 15:49:36 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lexer(t_data *data)
{
	if (!data->line)
		return (NULL);
	token_tolst(data, &data->tokens, 0);
	printf("\ntokens list\n");
	print_tokens(data->tokens);
	if (data->error)
		return (token_clear(data), false);
	if (!token_validation(data))
		return (token_lstclear(data), false);
	printf("\ntokens list merging\n");
	token_merge(data);
	// print_tokens(data->tokens);
	return (true);
}
// printf("\ntokens list\n");
// print_tokens(data->tokens);
// printf("\ntokens list merging\n");
