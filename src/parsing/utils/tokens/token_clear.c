/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:33:15 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 11:38:05 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to delete a node
 * then set it to NULL
*/

static void	token_del(t_token **node)
{
	if (!node || !*node)
		return ;
	free((*node)->value);
	(*node)->value = NULL;
	free(*node);
	*node = NULL;
}

/**
 * the purpose of this function is to delete all the nodes
 * then set the head to NULL
*/

void	token_clear(t_data *data)
{
	t_token	*crnt_node;
	t_token	*next_node;

	if (!data->tokens)
		return ;
	crnt_node = data->tokens;
	while (crnt_node)
	{
		next_node = crnt_node->next;
		token_del(&crnt_node);
		crnt_node = next_node;
	}
	data->tokens = NULL;
}
