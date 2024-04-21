/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:19:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 10:06:39 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to get the node with the given key
*/

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
