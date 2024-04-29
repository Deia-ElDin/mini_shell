/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 05:59:51 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 04:29:27 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static char	*env_set(t_env *env_node);
void		env_toarr(t_data *data);

/// @brief Used to convert a env node to a string
/// @param env_node The env node to convert
/// @return The string representation of the env node
static char	*env_set(t_env *env_node)
{
	char	*key;
	char	*value;
	bool	is_equal;

	key = env_node->key;
	value = env_node->value;
	is_equal = env_node->is_equal;
	if (is_equal && value)
		return (ft_strnjoin(3, key, "=", value));
	else if (is_equal)
		return (ft_strjoin(key, "="));
	else
		return (ft_strdup(key));
}

/// @brief Used to convert the env linked list to an array
/// @param data The main struct
void	env_toarr(t_data *data)
{
	t_env	*env_list;
	int		i;

	env_list = data->env_list;
	if (!env_list)
		return ;
	data->env = ft_calloc(env_lstsize(data) + 1, sizeof(char *));
	if (!data->env)
		exit_failure(data);
	i = 0;
	while (env_list)
	{
		data->env[i] = env_set(env_list);
		if (!data->env[i])
			exit_failure(data);
		env_list = env_list->next;
		i++;
	}
}
