/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/24 17:42:58 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_pipe(int pid, char *cmd, t_ast *ast_left, t_ast *ast_right)
{
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| !ast_left->end_flag || !ast_right->end_flag)
		waitpid(pid, NULL, 0);
}

static void	check_last_pipe(t_ast *ast_left, t_ast *ast_right, t_data *data)
{
	if (!ast_right->end_flag || !ast_left->end_flag)
	{
		if (dup2(data->saved_stdfds[1], 1) == -1)
			return (ft_putstr_fd("resetting FDs FAILED dup2 of 1\n", 2), 1);
	}
}

static void	call_child(char *cmd, char **args, t_data *data)
{
	char	*str;

	str = NULL;
	close(data->pipe[0]);
	dup2(data->pipe[1], 1);
	ft_putstr_fd("about to execute child\n", 2);
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

	str = NULL;
	str = gnl_till_null(my_pipes, str);
	ft_putstr_fd("clearing pipe\n", 2);
	close(my_pipes[1]);
	dup2(my_pipes[0], 0);
	free(str);
}

int	simple_cmd(t_ast *ast_left, t_ast *ast_right, t_data *data)
{
	char	*path;
	int		status;
	pid_t	pid;

	ft_putstr_fd("simple command\n", 2);
	status = 0;
	path = get_cmd_path(ast_left->cmd, data);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	if (data->redirect_flag == -1)
		dup2(data->file_fd, 0);
	else if (data->redirect_flag == 1)
		dup2(data->file_fd, 1);
	if (!path && data->pipe[0] >= 0)
		return (clear_pipe(data->pipe), 1);
	if (data->pipe[0] >= 0 || data->pipe[1] >= 0)
		check_last_pipe(ast_left, ast_right, data);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		call_child(path, ast_right->args, data);
	check_pipe(pid, path, ast_left, ast_right);
	if (data->pipe[0] >= 0 || data->pipe[1] >= 0)
	{
		close(data->pipe[1]);
		dup2(data->pipe[0], 0);
	}
	return (free(path), status);
}

int	pipe_cmd(t_data *data)
{
	ft_putstr_fd("pipe command\n", 2);
	if (pipe(data->pipe) == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	close(data->pipe[0]);
	dup2(data->pipe[1], 1);
	return (0);
}
