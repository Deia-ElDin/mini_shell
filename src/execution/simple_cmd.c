/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/20 19:17:24 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	call_child(char *cmd, t_ast *ast_right, t_data *data)
{
	char	*str;

	str = NULL;
	ft_putstr_fd("Executing child\n", 2);
	if (ast_right->head->head && ast_right->head->head->type == NODE_PIPE)
	{
		close(ast_right->head->head->pipe[0]);
		dup2(ast_right->head->head->pipe[1], 1);
		if (ast_right->end_flag)
			close(ast_right->head->head->pipe[1]);
	}
	if (cmd)
		execve(cmd, ast_right->cmd, data->env);
	if (ast_right->head->head && ast_right->head->head->type == NODE_PIPE
		&& (ast_right->head->head->pipe[0] < 0
			|| ast_right->head->head->pipe[1] < 0))
	{
		str = gnl_till_null(ast_right->head->head->pipe, str);
		free(str);
	}
	ft_putstr_fd("child execution FAILED\n", 2);
	exit(1);
}

static void	clear_pipe(int *my_pipes)
{
	char	*str;

	ft_putstr_fd("ERR: Clearing pipe\n", 2);
	str = NULL;
	str = gnl_till_null(my_pipes, str);
	close(my_pipes[1]);
	dup2(my_pipes[0], 0);
	free(str);
}

int	simple_cmd(t_ast *ast_left, t_ast *ast_right, t_data *data)
{
	char	*path;
	pid_t	pid;

	path = get_cmd_path(ast_left->cmd[0], data);
	if (check_for_redirs(ast_right, data))
		return (free(path), data->file_fd);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	if (!path && ast_left->head->head->type == NODE_PIPE)
		return (clear_pipe(ast_left->head->head->pipe), 1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		call_child(path, ast_right, data);
	else
	{
		pipe_for_next(data, ast_right);
		data->exit_status = check_for_sleep(pid, path, ast_right->end_flag);
	}
	return (free(path), data->exit_status);
}
