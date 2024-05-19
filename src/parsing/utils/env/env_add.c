/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:46:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/18 16:39:09 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to add a new node to the end of the linked list
/// @param data The main struct
/// @param new The new node to be added
void	env_add(t_data *data, t_env *new)
{
	t_env	*last_node;

	if (!new)
		return ;
	last_node = env_last(data);
	if (last_node)
		last_node->next = new;
	else
		data->env_list = new;
}
