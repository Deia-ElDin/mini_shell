/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:27:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 04:27:48 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	env_lstsize(t_data *data);

/// @brief Used to get the size of the env linked list
/// @param data The main struct
/// @return The size of the env linked list
int	env_lstsize(t_data *data)
{
	int		size;
	t_env	*crnt;

	size = 0;
	crnt = data->env_list;
	while (crnt && ++size)
		crnt = crnt->next;
	return (size);
}
