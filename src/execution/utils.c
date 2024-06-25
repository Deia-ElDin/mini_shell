/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:15:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 18:06:43 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_data *data)
{
	char	*cmd;

	if (!data->ast || data->ast->type != NODE_CMD || !data->ast->left->cmd)
		return (false);
	cmd = data->ast->left->cmd[0];
	if (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "unset")
		|| (!ft_strcmp(cmd, "export") && data->ast->right->cmd[1] != NULL
			&& !data->ast->pipe_exists && !data->ast->right->pipe_exists))
		return (true);
	return (false);
}

bool	is_builtin_with_out(t_data *data)
{
	char	*cmd;

	if (!data->ast || data->ast->type != NODE_CMD)
		return (false);
	cmd = data->ast->left->cmd[0];
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "pwd"))
		return (true);
	return (false);
}
