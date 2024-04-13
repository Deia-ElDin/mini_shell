/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:20:20 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 14:27:16 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->av = NULL;
	data->exit_status = 0;
	data->env_list = NULL;
	data->path = NULL;
	// data->history = NULL;
	// data->history = init_history(data->history);
	// data->history->current = data->history->head;
}

void	set_data(t_data *data, char **av, char **env)
{
	data->av = av;
	data->env = env;
	data->env_list = env_to_list(env);
	data->env = list_to_env(data->env_list);
	data->path = get_path(data->env_list);
}

void	free_data(t_data *data)
{
	// free_history(data->history);
	free_env_list(data->env_list);
	// free_path(data->path);
	free_env(data->env);
}
