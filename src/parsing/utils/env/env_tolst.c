/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tolst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 04:28:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 18:24:37 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to convert the env array to an env linked list
/// @param data The main struct
void	env_tolst(t_data *data)
{
	char	**key_value;
	bool	is_equal;
	int		i;

	data->env_list = NULL;
	if (!data->env)
		return ;
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
		{
			key_value = ft_split(data->env[i], '=');
			is_equal = ft_strchr(data->env[i], '=');
			env_new(data, key_value[0], key_value[1], is_equal);
			ft_free(&key_value, 'a');
		}
		else
			env_new(data, data->env[i], NULL, false);
		i++;
	}
}
