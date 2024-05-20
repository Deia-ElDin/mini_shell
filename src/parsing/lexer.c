/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/20 17:15:19 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

bool	lexer(t_data *data)
{
	if (!data->line)
		return (NULL);
	token_tolst(data, &data->tokens, 0);
	if (data->error)
		return (token_clear(data), false);
	if (!token_validation(data))
		return (token_clear(data), false);
	token_merge(data);
	// print_tokens(data->tokens);
	return (true);
}
// printf("\ntokens list\n");
// print_tokens(data->tokens);
// printf("\ntokens list merging\n");
// printf("\ntokens list\n");
// print_tokens(data->tokens);
// printf("\ntokens list merging\n");
