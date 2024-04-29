/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:13:31 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 05:59:15 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void		token_lstclear(t_data *data);

/// @brief Used to clear the token linked list
/// @param data The main struct
void	token_lstclear(t_data *data)
{
	t_token	*crnt_node;
	t_token	*next_node;

	if (!data->tokens)
		return ;
	crnt_node = data->tokens;
	while (crnt_node)
	{
		next_node = crnt_node->next;
		token_delone(&crnt_node);
		crnt_node = next_node;
	}
	data->tokens = NULL;
}
