/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:15:21 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/17 20:15:42 by dehamad          ###   ########.fr       */
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
