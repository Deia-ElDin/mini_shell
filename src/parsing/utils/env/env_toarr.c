/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 05:59:51 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 20:45:03 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to convert the env linked list to an array
/// @param data The main struct
void	env_toarr(t_data *data)
{
	t_env	*node;
	int		i;

	node = data->env_list;
	if (!node)
		return ;
	if (data->env_arr)
		ft_free(&data->env_arr, 'a');
	data->env_arr = ft_calloc(env_lstsize(data) + 1, sizeof(char *));
	if (!data->env_arr)
		return (data_status(data, 1));
	i = 0;
	while (node)
	{
		if (node->is_equal && node->value)
			data->env_arr[i] = ft_strnjoin(3, node->key, "=", node->value);
		else if (node->is_equal)
			data->env_arr[i] = ft_strjoin(node->key, "=");
		else
			data->env_arr[i] = ft_strdup(node->key);
		if (!data->env_arr[i])
			return (data_status(data, 1));
		node = node->next;
		i++;
	}
}
