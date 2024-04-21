/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:21:34 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 10:22:45 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_env	*env_update(t_data *data, char *env)
{
	t_env	*node;
	char	*key;
	char	*value;

	key = ft_strcdup(env, '=');
	value = ft_strchr(env, '=') + 1;
	node = env_get(data, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			exit_failure(data);
		node->is_equal = true;
	}
	else
	{
		node = env_new(data, env);
		env_add(data, node);
	}
	free(key);
	return (node);
}
