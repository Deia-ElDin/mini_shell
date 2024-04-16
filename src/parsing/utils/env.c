/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:38:46 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/16 19:11:53 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*env_to_list(t_data *data)
{
	char	**env;
	t_env	*env_list;
	t_env	*new_node;

	env = data->env;
	env_list = NULL;
	while (*env)
	{
		new_node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!new_node)
			exit_failure(data);
		new_node->key = ft_strdup(*env++);
		new_node->value = ft_strchr(new_node->key, '=');
		if (new_node->value)
		{
			*new_node->value = '\0';
			new_node->value++;
		}
		new_node->next = env_list;
		env_list = new_node;
	}
	return (env_list);
}

char	**list_to_env(t_data *data)
{
	t_env	*env_list;
	t_env	*tmp;
	char	**env;
	int		i;

	env_list = data->env_list;
	tmp = env_list;
	i = 0;
	while (tmp && ++i)
		tmp = tmp->next;
	env = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!env)
		exit_failure(data);
	i = 0;
	while (env_list)
	{
		env[i] = ft_strjoin_multi(3, env_list->key, "=", env_list->value);
		env_list = env_list->next;
		i++;
	}
	return (env);
}

t_env	*get_env(t_data *data, char *key)
{
	t_env	*env_list;
	t_env	*tmp;

	env_list = data->env_list;
	tmp = env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// char	**get_env_value(t_data *data, char *key)
// {
// 	t_env	*env_list;
// 	t_env	*tmp;
// 	char	**ret;

// 	env_list = data->env_list;
// 	tmp = env_list;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->key, key))
// 		{
// 			ret = ft_split(tmp->value, ':');
// 			if (!ret)
// 				exit_failure(data);
// 			return (ret);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// void	free_env_list(t_env *env_list)
// {
// 	t_env	*tmp;

// 	while (env_list)
// 	{
// 		tmp = env_list;
// 		env_list = env_list->next;
// 		free(tmp->key);
// 		free(tmp);
// 	}
// }

// void	free_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 		free(env[i++]);
// 	free(env);
// }

// void	free_path(t_env *path)
// {
// 	free(path->key);
// 	free(path->value);
// 	free(path);
// }