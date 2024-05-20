/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:26:40 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 17:44:55 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_concat(t_data *data, char *key, char *value)
{
	t_env	*node;
	char	*new_value;

	node = env_get(data, key);
	if (node)
	{
		new_value = ft_strjoin(node->value, value);
		if (!new_value)
			return (data_status(data, 1));
		ft_free(&node->value, 'p');
		node->value = new_value;
	}
	else
		env_new(data, key, value, true);
	env_toarr(data);
}
