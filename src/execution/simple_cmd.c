/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/28 15:33:43 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	call_child(char *cmd, t_ast *ast, t_data *data)
{
	if (ast->head->in_exists)
		dup2(ast->head->file_fd, STDIN_FILENO);
	if (ast->head->prev_exists)
	{
		dup2(ast->head->prev_pipe[READ_END], STDIN_FILENO);
		close(ast->head->prev_pipe[READ_END]);
	}
	if (ast->head->pipe_exists)
	{
		close(ast->head->pipe[READ_END]);
		dup2(ast->head->pipe[WRITE_END], STDOUT_FILENO);
		close(ast->head->pipe[WRITE_END]);
	}
	if (ast->head->out_exists)
		dup2(ast->head->file_fd, STDOUT_FILENO);
	if (is_builtin_with_out(data))
		builtins_with_out(data);
	else if (cmd)
	{
		execve(cmd, ast->cmd, data->env);
		ft_putstr_fd("child execution FAILED\n", 2);
		exit(1);
	}
	exit(1);
}

static void	call_parent(pid_t pid, char *path, t_ast *ast, t_data *data)
{
	data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	if (ast->prev_exists)
		close(ast->prev_pipe[READ_END]);
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
		pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork failed\n", 2);
	if (pid < 0)
		data->exit_status = pid;
	if (pid == 0)
		call_child(path, ast->right, data);
	else if (pid > 0)
		call_parent(pid, path, ast, data);
	return (free(path), data->exit_status);
}
