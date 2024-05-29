/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:49:47 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 17:51:27 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_init(t_data *data, char *key, char *value, bool is_equal );
void			env_new(t_data *data, char *key, char *value, bool is_equal );

/// @brief Used to create a new env node and initialize it
/// @param data The main struct
/// @param key_value_arr The key value pair array, key[0], value[1]
/// @return 
static t_env	*env_init(t_data *data, char *key, char *value, bool is_equal )
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = NULL;
	new_node->value = NULL;
	if (is_equal)
		new_node->is_equal = true;
	else
		new_node->is_equal = false;
	if (key)
	{
		new_node->key = ft_strdup(key);
		if (!new_node->key)
			return (data->exit_status = 1, env_free(new_node), NULL);
	}
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (data->exit_status = 1, env_free(new_node), NULL);
	}
	return (new_node);
}

/// @brief Used to create a new env node
/// @param data The main struct
/// @param key_value_pair A pointer to the key value pair
void	env_new(t_data *data, char *key, char *value, bool is_equal )
{
	t_env	*new_node;

	new_node = env_init(data, key, value, is_equal);
	if (!new_node)
		return (data_status(data, 1));
	env_add(data, new_node);
}
