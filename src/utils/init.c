/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:32:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/19 23:34:17 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * the purpose of this function is to initialize the data structure
 * we will set the line to NULL
 * we will set the env_list to NULL
 * we will set the env to NULL
 * we will set the path to NULL
 * we will set the tokens to NULL
 * we will set the ast to NULL
 * we will set the exit_status to 0
 
 * if the env is not NULL
 * we will set the env to the env pointer (so we can use it inside the next 2 fn)
 * we will convert the env to a linked list
 * we will convert the same linked list we created to a ** array
 * we will use the get_env function to get the PATH t_env node
 * we will target the node value
 * then we will split the value by the : character
 * then we store the result into the path variable
*/

void	init_data(t_data *data, char **env)
{
	data->line = NULL;
	data->env_list = NULL;
	data->env = NULL;
	data->path = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	data->exit_status = 0;
	if (env)
	{
		data->env = env;
		data->env_list = env_to_list(data);
		data->env = list_to_env(data);
		data->path = ft_split(get_env(data, "PATH")->value, ':');
		if (!data->path)
			exit_failure(data);
	}
}
