/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:15:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/14 16:27:14 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void    add_env(t_data *data, char *key, char *value)
// {
//     t_env   *new_node;

//     new_node = (t_env *)ft_calloc(1, sizeof(t_env));
//     if (!new_node)
//         exit(1);
//     new_node->key = key;
//     new_node->value = value;
//     new_node->next = data->env_list;
//     data->env_list = new_node;
// }