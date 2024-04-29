/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:32:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/29 23:00:30 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Used to initialize the data structure
/// @param data The main struct
/// @param env A double pointer to the environment variables
void	data_init(t_data *data, char **env)
{
	data->line = NULL;
	data->env_list = NULL;
	data->env = NULL;
	data->path = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	data->error = false;
	data->exit_status = 0;
	data->highest_token = TOKEN_AND;
	if (env)
	{
		data->env = env;
		env_tolst(data);
		env_toarr(data);
		data->path = ft_split(env_get(data, "PATH")->value, ':');
		if (!data->path)
			exit_failure(data);
	}
}

/**
 * The purpose of this function is to initialize the data structure
 * The purpose of the data->error: is to use it as a flag where 
 * we need to stop a stage of the execution of the program,
 * i.e if we found a quote error while creating the tokens list, 
 * since we can't validate the quotes in the token_validation function
*/

/// @brief Used to reset the data structure after each user input
/// @param data The main struct
void	data_reset(t_data *data)
{
	token_lstclear(data);
	ast_lstclear(data);
	ft_free(&data->line, 'p');
	data->exit_status = 0;
}

/// @brief Used to free the data structure at the end of the program
/// @param data The main struct
void	data_free(t_data *data)
{
	env_lstclear(data);
	token_lstclear(data);
	ast_lstclear(data);
	ft_free(&data->env, 'a');
	ft_free(&data->path, 'a');
	ft_free(&data->line, 'p');
}
