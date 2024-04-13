/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:37:28 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/12 12:57:35 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char    *get_env_value(char *key, t_env *env_list)
{
    while (env_list)
    {
        if (ft_strcmp(key, env_list->key) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return (NULL);
}

void    cd(t_data *data)
{
    char    *path;

    printf("data->av[1]: %s\n", data->av[1]);
    printf("data->av[1] + 1: %s\n", data->av[1] + 1);
    if (!data->av[1])
        path = get_env_value("HOME", data->env_list);
    else if (data->av[1][0] == '~')
        path = ft_strjoin(get_env_value("HOME", data->env_list), data->av[1] + 1);
    else
        path = ft_strdup(data->av[1]);
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: no such file or directory: ", 2);
        ft_putendl_fd(data->av[1], 2);
        data->exit_status = 1;
    }
    else
        data->exit_status = 0;
    free(path);
}