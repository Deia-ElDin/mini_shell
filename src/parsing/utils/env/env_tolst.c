/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tolst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 04:28:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 20:20:37 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to convert the array to a linked list
*/

void	env_tolst(t_data *data)
{
	int	i;

	data->env_list = NULL;
	if (!data->env)
		return ;
	i = -1;
	while (data->env[++i])
		env_add(data, env_new(data, data->env[i]));
}
