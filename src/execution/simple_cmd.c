/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 14:52:57 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	call_child(char *cmd, t_ast *ast, t_data *data)
{
	ft_putstr_fd("Executing child\n", 2);
	if (cmd)
		execve(cmd, ast->cmd, data->env);
	ft_putstr_fd("child execution FAILED\n", 2);
	exit(1);
}

// static void	clear_pipe(int *my_pipes)
// {
// 	char	*str;

// 	ft_putstr_fd("ERR: Clearing pipe\n", 2);
// 	str = NULL;
// 	str = gnl_till_null(my_pipes, str);
// 	close(my_pipes[1]);
// 	dup2(my_pipes[0], 0);
// 	free(str);
// }

int	simple_cmd(t_data *data)
{
	t_ast	*ast;
	char	*path;
	pid_t	pid;

	ast = data->ast;
	path = get_cmd_path(ast->left->cmd[0], data);
	if (!check_for_redirs(ast->right, data))
		return (free(path), data->file_fd);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	// if (!path && ast->left->head->head->type == NODE_PIPE)
	// 	return (clear_pipe(ast->left->head->head->pipe), 1);
	pid = fork();
	ft_putstr_fd("PID: \n", 2);
	ft_putnbr_fd(pid, 2);
	ft_putstr_fd("\n", 2);
	if (pid < 0)
	{
		data->exit_status = pid;
		return (pid);
	}
	if (pid == 0)
		call_child(path, ast->right, data);
	else
		data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	return (free(path), data->exit_status);
}
