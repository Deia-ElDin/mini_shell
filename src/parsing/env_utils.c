/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:38:46 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/11 18:10:52 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_to_list(char **env)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (*env)
	{
		// printf("env[%d]: %s\n", i++, *env);
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			exit(1);
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

char	**list_to_env(t_env *env_list)
{
	char	**env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env_list;
	while (tmp && ++i)
		tmp = tmp->next;
	env = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!env)
		exit(1);
	i = 0;
	while (env_list)
	{
		env[i] = ft_strjoin_multi(3, env_list->key, "=", env_list->value);
		env_list = env_list->next;
		i++;
	}
	return (env);
}

t_env	*get_path(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->key);
		free(tmp);
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}