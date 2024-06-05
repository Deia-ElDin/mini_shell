/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/05 10:19:12 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(char *cmd, t_ast *ast, t_data *data)
{
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

static void	call_child(char *cmd, t_ast *ast, t_data *data)
{
	if (ast->redir_in->exists)
		dup2(ast->redir_in->fd, STDIN_FILENO);
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
	if (ast->redir_out->exists)
		dup2(ast->redir_out->fd, STDOUT_FILENO);
	else if (ast->redir_append->exists)
		dup2(ast->redir_append->fd, STDOUT_FILENO);
	execute_command(cmd, ast, data);
}

static void	call_parent(pid_t pid, char *path, t_ast *ast, t_data *data)
{
	data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	if (ast->prev_exists && !ast->right->heredoc->exists)
		close(ast->prev_pipe[READ_END]);
	else if (ast->prev_exists && ast->right->heredoc->exists)
		close(ast->right->heredoc->fd);
	if (ast->pipe_exists)
		close(ast->pipe[WRITE_END]);
	if (ast->redir_out->exists)
		close(ast->redir_out->fd);
	else if (ast->redir_append->exists)
		close(ast->redir_append->fd);
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
		return (free(path), 1);
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
