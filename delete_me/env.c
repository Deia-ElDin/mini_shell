/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:38:46 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/17 17:31:11 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	update_env(t_data *data, char *env)
// {
// 	t_env	*tmp;

// 	tmp = data->env_list;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->key, env))
// 		{
// 			free(tmp->value);
// 			tmp->value = ft_strchr(env, '=');
// 			if (tmp->value)
// 			{
// 				*tmp->value = '\0';
// 				tmp->value++;
// 			}
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	add_env(data, env);
// }

/**
 * the purpose of this function is to convert the **envs to a linked list
 * of t_env nodes
 * we malloc a new t_env node 
 * we assign the key to the first env and we increment the env pointer
 * we won't malloc for the value
 * we will create the value in few different steps
 * 1- we look for the = character in the key
 * 2- if we find it we assign the value to the address of the = character
 * 3- we replace the = char with a \0 byte (now the key is null terminated)
 * 4- we increment the value pointer to point to the char after the \0 byte
 * now we have a null terminated key and a value that starts after the = char
*/

// t_env	*env_to_list(t_data *data)
// {
// 	char	**env;
// 	t_env	*env_list;
// 	t_env	*new_node;

// 	env = data->env;
// 	env_list = NULL;
// 	while (*env)
// 	{
// 		new_node = (t_env *)ft_calloc(1, sizeof(t_env));
// 		if (!new_node)
// 			exit_failure(data);
// 		new_node->key = ft_strdup(*env++);
// 		new_node->value = ft_strchr(new_node->key, '=');
// 		if (new_node->value)
// 		{
// 			*new_node->value = '\0';
// 			new_node->value++;
// 		}
// 		new_node->next = env_list;
// 		env_list = new_node;
// 	}
// 	return (env_list);
// }

/**
 * the purpose of this function is to convert the linked list to a ** array
 * we will malloc a ** array so we need the length of the linked list
 * we will loop through the linked list and get the i (length of the linked list)
 * we will malloc with the length of the linked list + 1 (for the NULL)
 * we used ft_calloc to set all the pointers to NULL (malloc and initialize)
 * we loop through the linked list and we will join the key and value
 * we will use the ft_strnjoin function to join the key, =, and value
*/

// char	**list_to_env(t_data *data)
// {
// 	t_env	*env_list;
// 	t_env	*tmp;
// 	char	**env;
// 	int		i;

// 	env_list = data->env_list;
// 	tmp = env_list;
// 	i = 0;
// 	while (tmp && ++i)
// 		tmp = tmp->next;
// 	env = (char **)ft_calloc((i + 1), sizeof(char *));
// 	if (!env)
// 		exit_failure(data);
// 	i = 0;
// 	while (env_list)
// 	{
// 		env[i] = ft_strnjoin(3, env_list->key, "=", env_list->value);
// 		env_list = env_list->next;
// 		i++;
// 	}
// 	return (env);
// }

/**
 * the purpose of this function is to get the value of the key
 * this is a generic function that can be used whenever needed
 * it returns the t_env node or NULL
*/

// t_env	*get_env_node(t_data *data, char *key)
// {
// 	t_env	*env_list;
// 	t_env	*tmp;

// 	env_list = data->env_list;
// 	tmp = env_list;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->key, key))
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }
