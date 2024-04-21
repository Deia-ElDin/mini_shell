/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:33:15 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 11:36:04 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to delete a node
 * then set it to NULL
*/

static void	env_del(t_env **node)
{
	if (!node || !*node)
		return ;
	free((*node)->key);
	free((*node)->value);
	(*node)->key = NULL;
	(*node)->value = NULL;
	free(*node);
	*node = NULL;
}

/**
 * the purpose of this function is to delete all the nodes
 * then set the head to NULL
*/

void	env_clear(t_data *data)
{
	t_env	*crnt_node;
	t_env	*next_node;

	if (!data->env_list)
		return ;
	crnt_node = data->env_list;
	while (crnt_node)
	{
		next_node = crnt_node->next;
		env_del(&crnt_node);
		crnt_node = next_node;
	}
	data->env_list = NULL;
}
