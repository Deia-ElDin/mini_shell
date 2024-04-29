/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:10:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 04:24:47 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_env	*env_last(t_data *data);

/// @brief Used to get the last node of the linked list
/// @param data The main struct
/// @return The last node of the linked list
t_env	*env_last(t_data *data)
{
	t_env	*last_node;

	if (!data->env_list)
		return (NULL);
	last_node = data->env_list;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}
