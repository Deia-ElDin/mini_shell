/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/10 15:09:18 by melshafi         ###   ########.fr       */
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
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(1);
}

static void	call_child(char *cmd, t_ast *ast, t_data *data)
{
	if (in_exists(ast))
		dup2(*(ast->head->in_fd), STDIN_FILENO);
	if (ast->head->prev_exists && !heredoc_exists(ast))
	{
		dup2(ast->head->prev_pipe[READ_END], STDIN_FILENO);
		close(ast->head->prev_pipe[READ_END]);
	}
	else if (ast->head->prev_exists && heredoc_exists(ast))
		dup2(*(ast->head->in_fd), STDIN_FILENO);
	if (ast->head->pipe_exists)
	{
		close(ast->head->pipe[READ_END]);
		dup2(ast->head->pipe[WRITE_END], STDOUT_FILENO);
		close(ast->head->pipe[WRITE_END]);
	}
	if (out_exists(ast))
		dup2(*(ast->head->out_fd), STDOUT_FILENO);
	else if (append_exists(ast))
		dup2(*(ast->head->out_fd), STDOUT_FILENO);
	execute_command(cmd, ast, data);
}

static void	call_parent(pid_t pid, char *path, t_ast *ast, t_data *data)
{
	data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	if (ast->prev_exists && !heredoc_exists(ast))
		close(ast->prev_pipe[READ_END]);
	else if (ast->prev_exists && heredoc_exists(ast))
		close(*(ast->in_fd));
	else if (in_exists(ast))
		close(*(ast->in_fd));
	if (ast->pipe_exists)
		close(ast->pipe[WRITE_END]);
	if (out_exists(ast))
		close(*(ast->out_fd));
	else if (append_exists(ast))
		close(*(ast->out_fd));
}

int	simple_cmd(t_data *data)
{
	t_ast	*ast;
	char	*path;
	pid_t	pid;

	ast = data->ast;
	pid = 1;
	path = get_cmd_path(ast->left->cmd[0], data);
	if (!check_for_redirs(ast->right->right))
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
