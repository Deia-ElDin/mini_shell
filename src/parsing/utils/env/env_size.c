/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:51:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 11:46:53 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to get the size of the linked list
*/

int	env_size(t_data *data)
{
	int		size;
	t_env	*crnt;

	size = 0;
	crnt = data->env_list;
	while (crnt && ++size)
		crnt = crnt->next;
	return (size);
}
