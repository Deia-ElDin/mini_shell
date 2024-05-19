/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:43:14 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 17:51:27 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to set the value of an existing key in the linked list
/// @param data The main struct
/// @param key The key to set
/// @param value The value to set
void	env_set(t_data *data, char *key, char *value, bool is_equal )
{
	t_env	*node;

	node = env_get(data, key);
	if (node)
	{
		if (node->value)
			ft_free(&node->value, 'p');
		if (value && *value)
		{
			node->is_equal = true;
			node->value = ft_strdup(value);
			if (!node->value)
				return (data_status(data, 1));
		}
		else
			node->value = NULL;
	}
	else
		env_new(data, key, value, is_equal);
	env_toarr(data);
}
