/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:25:21 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/16 16:14:02 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_unset(t_data *data)
{
	t_env	*current;
	t_env	*previous;
	char	*key;

	key = data->ast->right->cmd[1];
	if (!data || !key)
		return ;
	printf("key %s\n", key);
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
