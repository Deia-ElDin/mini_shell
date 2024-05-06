/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/06 12:39:58 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (token_clear(data), false);
	printf("\ntokens list merging\n");
	token_merge(data);
	print_tokens(data->tokens);
	return (true);
}
