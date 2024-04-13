/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:45:17 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/12 19:01:20 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    builtins(t_data *data)
{
    printf("data->line = %s\n", data->line);
    if (ft_strcmp(data->line, "cd") == 0)
        cd(data);
    // else if (ft_strcmp(data->av[0], "echo") == 0)
    //     echo(data);
    // else if (ft_strcmp(data->av[0], "env") == 0)
    //     env(data);
    // else if (ft_strcmp(data->av[0], "exit") == 0)
    //     exit_shell(data);
    // else if (ft_strcmp(data->av[0], "export") == 0)
    //     export(data);
    // else if (ft_strcmp(data->av[0], "pwd") == 0)
    //     pwd(data);
    // else if (ft_strcmp(data->av[0], "unset") == 0)
    //     unset(data);
    else
        data->exit_status = 127;
}
