/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:49:47 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 04:31:27 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_env	*env_new(t_data *data, char *env);

/// @brief Used to create a new env node
/// @param data The main struct
/// @param env A pointer to the environment variable
/// @return The new env node
t_env	*env_new(t_data *data, char *env)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		exit_failure(data);
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->is_equal = false;
	new_node->key = ft_strdup(env);
	if (!new_node->key)
		exit_failure(data);
	new_node->value = ft_strchr(new_node->key, '=');
	if (new_node->value)
	{
		new_node->is_equal = true;
		*new_node->value = '\0';
		new_node->value++;
		new_node->value = ft_strdup(new_node->value);
		if (!new_node->value)
			exit_failure(data);
	}
	return (new_node);
}

/**
 * the purpose of this function is to create a new node
 * key is the key of the environment variable
 * value is the value of the environment variable
 * key = ft_strdup to the whole env string, 
 * then if there's = sign we null terminate it
 * and value is the rest of the string
*/
