/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 07:25:46 by dehamad          ###   ########.fr       */
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
		return (token_lstclear(data), false);
	if (!token_validation(data))
		return (token_lstclear(data), false);
	printf("\ntokens list merging\n");
	token_merge(data);
	print_tokens(data->tokens);
	return (true);
}
