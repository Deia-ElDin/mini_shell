/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:32:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/17 23:49:12 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data, char **env)
{
	data->env_list = NULL;
	data->env = NULL;
	// data->av = NULL;
	data->path = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	data->line = NULL;
	data->exit_status = 0;
	// data->av = av;
	data->env = env;
	data->env_list = env_to_list(data);
	data->env = list_to_env(data);
	data->path = ft_split(get_env(data, "PATH")->value, ':');
	if (!data->path)
		exit_failure(data);
}
