/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:32:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/21 18:04:08 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Used to update the SHLVL environment variable
/// @param data The main struct
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

/// @brief Used to initialize the data structure
/// @param data The main struct
/// @param env A double pointer to the environment variables
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
	dup2(data->std_fds[0], 0);
	dup2(data->std_fds[1], 1);
	if (env)
	{
		data->env = env;
		env_tolst(data);
		update_shlvl(data);
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

/**
 * The purpose of this function is to initialize the data structure
 * The purpose of the data->error: is to use it as a flag where
 * we need to stop a stage of the execution of the program,
 * i.e if we found a quote error while creating the tokens list,
 * since we can't validate the quotes in the token_validation function
*/

/// @brief Used to update the exit status in the data structure
/// @param data The main struct
/// @param exit_status The exit status to be updated
void	data_status(t_data *data, int exit_status)
{
	data->exit_status = exit_status;
}

/// @brief Used to reset the data structure after each user input
/// @param data The main struct
void	data_reset(t_data *data)
{
	dup2(data->std_fds[1], 1);
	dup2(data->std_fds[0], 0);
	token_clear(data);
	ast_lstclear(data);
	ft_free(&data->line, 'p');
	data->exit_status = 0;
}

/// @brief Used to free the data structure at the end of the program
/// @param data The main struct
void	data_free(t_data *data)
{
	token_clear(data);
	env_lstclear(data);
	ast_lstclear(data);
	ft_free(&data->line, 'p');
	ft_free(&data->line, 'p');
	ft_free(&data->path, 'a');
	ft_free(&data->env_arr, 'a');
	ft_free(&data->env_arr, 'a');
}
