/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:15:21 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 14:20:06 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lexer(t_data *data)
{
	if (!data->line)
		return (NULL);
	token_tolst(data, &data->tokens, 0);
	// print_tokens(data->tokens);
	if (data->error)
		return (token_lstclear(data), false);
	if (!token_validation(data))
		return (token_lstclear(data), false);
	token_reorder(data);
	// print_tokens(data->tokens);
	token_merge(data);
	// print_tokens(data->tokens);
	return (true);
}
