/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:32:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 10:37:45 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_data *data)
{
	t_env	*shlvl_env;
	t_atoi	ret;
	int		shlvl;
	char	*shlvl_str;

	shlvl_env = env_get(data, "SHLVL");
	if (shlvl_env && shlvl_env->value)
	{
		ret = ft_atoi(shlvl_env->value);
		if (ret.error)
			return (data_status(data, 1));
		shlvl = ret.nbr;
		shlvl++;
	}
	else
		shlvl = 1;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (data_status(data, 1));
	env_set(data, "SHLVL", shlvl_str, true);
	ft_free(&shlvl_str, 'p');
}

void	data_init(t_data *data, char **env)
{
	t_env	*path_env;

	data->line = NULL;
	data->env_list = NULL;
	data->env = NULL;
	data->env_arr = NULL;
	data->env_arr = NULL;
	data->path = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	data->error = false;
	data->exit_status = 0;
	// dup2(data->std_fds[0], 0);
	// dup2(data->std_fds[1], 1);
	if (env)
	{
		data->env = env;
		env_tolst(data);
		update_shlvl(data);
		env_toarr(data);
		path_env = env_get(data, "PATH");
		if (path_env && path_env->value)
		{
			data->path = ft_split(path_env->value, ':');
			if (!data->path)
				return (data_status(data, 1));
		}
	}
}

void	data_status(t_data *data, int exit_status)
{
	data->exit_status = exit_status;
}

void	data_reset(t_data *data)
{
	while (data->ast->head)
		data->ast = data->ast->head;
	while (data->tokens->prev)
		data->tokens = data->tokens->prev;
	data->error = false;
	token_lstclear(data);
	ast_lstclear(data);
	ft_free(&data->line, 'p');
}

/// @brief Used to free the data structure at the end of the program
/// @param data The main struct
void	data_free(t_data *data)
{
	while (data->ast->head)
		data->ast = data->ast->head;
	while (data->tokens->prev)
		data->tokens = data->tokens->prev;
	token_lstclear(data);
	env_lstclear(data);
	ast_lstclear(data);
	ft_free(&data->line, 'p');
	ft_free(&data->line, 'p');
	ft_free(&data->path, 'a');
	ft_free(&data->env_arr, 'a');
}
