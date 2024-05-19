/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:18 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/18 17:00:42 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(t_data *data, char *key)
{
	t_env	*current;
	t_env	*previous;

	if (data == NULL || key == NULL)
		return ;
	current = data->env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				data->env_list = current->next;
			env_free(current);
			env_toarr(data);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
