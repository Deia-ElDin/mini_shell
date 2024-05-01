/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/29 15:52:47 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	call_child(char *cmd, char **args, int last, t_data *data)
{
	char	*str;

	str = NULL;
	ft_putstr_fd("Executing child\n", 2);
	if (data->pipe[0] >= 0 || data->pipe[1] >= 0)
	{
		close(data->pipe[0]);
		dup2(data->pipe[1], 1);
		if (!last)
			close(data->pipe[1]);
	}
	if (cmd)
		execve(cmd, args, data->env);
	if (data->pipe != NULL)
	{
		str = gnl_till_null(data->pipe, str);
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

	path = get_cmd_path(ast_left->cmd, data);
	if (check_for_redirs(ast_right, data))
		return (free(path), data->file_fd);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	if (!path && data->pipe[0] >= 0)
		return (clear_pipe(data->pipe), 1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		call_child(path, ast_right->args, ast_right->end_flag, data);
	else
	{
		pipe_for_next(data, ast_left->end_flag + ast_right->end_flag);
		data->exit_status = check_for_sleep(pid, path, ast_right->end_flag);
	}
	return (free(path), data->exit_status);
}

int	pipe_cmd(t_ast *ast, t_data *data)
{
	if (data->pipe[0] == -1 && data->pipe[1] == -1)
	{
		if (pipe(data->pipe) == -1)
			return (ft_putstr_fd("ERR\n", 2), 1);
	}
	if (ast->left->left && ast->left->right)
		exec_ast(ast->left, data);
	if (ast->right->left && ast->right->right)
		exec_ast(ast->right, data);
	return (0);
}
