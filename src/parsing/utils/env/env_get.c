/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:19:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/18 16:39:32 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to get the node with the given key
/// @param data The main struct
/// @param key The key to search for in the env list
/// @return The node with the given key
t_env	*env_get(t_data *data, char *key)
{
	t_env	*node;

	if (!data->env_list)
		return (NULL);
	node = data->env_list;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}
