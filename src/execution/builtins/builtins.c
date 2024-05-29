/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:45:17 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/28 11:49:00 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(t_data *data)
{
	char	*cmd;

	cmd = data->ast->right->cmd[0];
	if (!cmd)
		return (data_status(data, 1));
	if (ft_strcmp(cmd, "cd") == 0)
		cd(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_shell(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		env_unset(data);
	else
		return ;
}

void	builtins_with_out(t_data *data)
{
	char	*cmd;

	cmd = data->ast->right->cmd[0];
	if (!cmd)
		return (data_status(data, 1));
	if (ft_strcmp(cmd, "echo") == 0)
		echo(data);
	else if (ft_strcmp(cmd, "env") == 0)
		env(data);
	else if (ft_strcmp(cmd, "export") == 0)
		export(data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		pwd(data);
	else
		return ;
}
