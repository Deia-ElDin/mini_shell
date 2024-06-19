/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/19 15:46:50 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(char *cmd, t_ast *ast, t_data *data)
{
	struct stat	path_stat;


	if (is_builtin_with_out(data))
	{
		builtins_with_out(data);
		exit(data->exit_status);
	}
	else if (!stat(ast->cmd[0], &path_stat) && S_ISDIR(path_stat.st_mode)
		&& (print_error(ast->cmd[0], "Is a directory"), 1))
		exit(126);
	else if (S_ISREG(path_stat.st_mode) && access(cmd, X_OK) > 0
		&& (print_error(ast->cmd[0], "Permission denied"), 1))
		exit(126);
	else if (cmd)
		execve(cmd, ast->cmd, data->env_arr);
	if (!ft_strncmp(ast->cmd[0], "/", 1) && !S_ISREG(path_stat.st_mode)
		&& !S_ISDIR(path_stat.st_mode))
		print_error(ast->cmd[0], "No such file or directory");
	else if (ast->cmd[0] && cmd && S_ISREG(path_stat.st_mode))
		print_error(ast->cmd[0], "command not found");
	else
		print_error(NULL, "command not found");
	exit(127);
}

static void	call_child(char *cmd, t_ast *ast, t_data *data)
{
	if (ast->head->in_exists)
		dup2(ast->head->file_fd, STDIN_FILENO);
	if (ast->head->prev_exists && !ast->heredoc->exists)
	{
		dup2(ast->head->prev_pipe[READ_END], STDIN_FILENO);
		close(ast->head->prev_pipe[READ_END]);
	}
	else if (ast->head->prev_exists && ast->heredoc->exists)
		dup2(ast->heredoc->fd, STDIN_FILENO);
	if (ast->head->pipe_exists)
	{
		close(ast->head->pipe[READ_END]);
		dup2(ast->head->pipe[WRITE_END], STDOUT_FILENO);
		close(ast->head->pipe[WRITE_END]);
	}
	if (ast->head->out_exists)
		dup2(ast->head->file_fd, STDOUT_FILENO);
	execute_command(cmd, ast, data);
}

static void	call_parent(pid_t pid, char *path, t_ast *ast, t_data *data)
{
	data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	// ft_putstr_fd("1Testing exit code: ", 2);
	// ft_putnbr_fd(data->exit_status, 2);
	// ft_putstr_fd("\n", 2);
	if (ast->prev_exists && !ast->right->heredoc->exists)
		close(ast->prev_pipe[READ_END]);
	else if (ast->prev_exists && ast->right->heredoc->exists)
		close(ast->right->heredoc->fd);
	if (ast->pipe_exists)
		close(ast->pipe[WRITE_END]);
	if (ast->out_exists)
		close(ast->file_fd);
}

int	simple_cmd(t_data *data)
{
	t_ast	*ast;
	char	*path;
	pid_t	pid;

	ast = data->ast;
	pid = 1;
	path = get_cmd_path(ast->left->cmd[0], data);
	if (!check_for_redirs(ast->right))
		return (free(path), ast->right->file_fd);
	if (is_builtin(data))
		builtins(data);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_putstr_fd("fork failed\n", 2);
		if (pid < 0)
			data->exit_status = pid;
		if (pid == 0)
			call_child(path, ast->right, data);
		else if (pid > 0)
			call_parent(pid, path, ast, data);
	}
	// ft_putstr_fd("3Testing exit code: ", 2);
	// ft_putnbr_fd(data->exit_status, 2);
	// ft_putstr_fd("\n", 2);
	return (free(path), data->exit_status);
}
