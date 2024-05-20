/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:12:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/18 16:38:57 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to clear the env linked list
/// @param data The main struct
void	env_lstclear(t_data *data)
{
	t_env	*crnt_node;
	t_env	*next_node;

	if (!data->env_list)
		return ;
	crnt_node = data->env_list;
	while (crnt_node)
	{
		next_node = crnt_node->next;
		env_free(crnt_node);
		crnt_node = next_node;
	}
	data->env_list = NULL;
}
