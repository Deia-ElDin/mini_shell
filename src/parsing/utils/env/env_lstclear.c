/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:12:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 04:12:54 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	env_del(t_env **node);
void		env_lstclear(t_data *data);

/// @brief Used to delete an env node
/// @param node The node to delete
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

/// @brief Used to clear the env linked list
/// @param data The main struct
void	env_lstclear(t_data *data)
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
