/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tolst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 04:28:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/19 13:56:06 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to convert the env array to an env linked list
/// @param data The main struct
void	env_tolst(t_data *data)
{
	char	*key;
	char	*value;
	int		i;

	data->env_list = NULL;
	if (!data->env)
		return ;
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
		{
			key = ft_strcdup(data->env[i], '=');
			value = ft_strdup(ft_strchr(data->env[i], '=') + 1);
			if (!key || !value)
				return (data_status(data, 1));
			env_new(data, key, value, true);
			ft_free(&key, 'p');
			ft_free(&value, 'p');
		}
		else
			env_new(data, data->env[i], NULL, false);
		i++;
	}
}
