/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 05:59:51 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 11:19:34 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to convert a node to a string
*/

static char	*env_set(t_env *env_node)
{
	char	*key;
	char	*value;
	bool	is_equal;

	key = env_node->key;
	value = env_node->value;
	is_equal = env_node->is_equal;
	if (is_equal && value)
		return (ft_strjoin_multi(3, key, "=", value));
	else if (is_equal)
		return (ft_strjoin(key, "="));
	else
		return (ft_strdup(key));
}

/**
 * the purpose of this function is to convert the linked list to an array
*/

void	env_toarr(t_data *data)
{
	t_env	*env_list;
	int		i;

	env_list = data->env_list;
	if (!env_list)
		return ;
	data->env = ft_calloc(env_size(data) + 1, sizeof(char *));
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
