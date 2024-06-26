/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:41:27 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/26 13:51:46 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_command_validity(char *path, char *cmd, struct stat path_stat)
{
	if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		&& S_ISDIR(path_stat.st_mode)
		&& (print_error(cmd, "Is a directory"), 1))
		return (1);
	else if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		&& !access(path, F_OK) && !(path_stat.st_mode & S_IXUSR))
		return (print_error(cmd, "Permission denied"), 1);
	return (0);
}

static int	execute_command(char *cmd, t_ast *ast, t_data *data)
{
	struct stat	path_stat;

	if (cmd)
		stat(cmd, &path_stat);
	if (is_builtin_with_out(data))
	{
		builtins_with_out(data);
		data_free(data);
		return (free(cmd), exit(data->exit_status), 0);
	}
	else if (cmd && check_command_validity(cmd, ast->cmd[0], path_stat)
		&& (data_free(data), free(cmd), 1))
		exit(126);
	else if (cmd)
		execve(cmd, ast->cmd, data->env_arr);
	if (ast->cmd && ast->cmd[0] && !ft_strncmp(ast->cmd[0], "/", 1)
		&& !S_ISREG(path_stat.st_mode) && !S_ISDIR(path_stat.st_mode))
		print_error(ast->cmd[0], "No such file or directory");
	else if (ast->cmd && ast->cmd[0])
		print_error(ast->cmd[0], "command not found");
	else
		print_error(NULL, "command not found");
	if (cmd)
		free(cmd);
	return (data_free(data), exit(127), 0);
}

void	call_child(char *cmd, t_ast *ast, t_data *data)
{
	if (ast->head->prev_exists && !in_exists(ast))
		dup2(ast->head->prev_pipe[READ_END], STDIN_FILENO);
	else if (in_exists(ast))
		dup2(*(ast->head->in_fd), STDIN_FILENO);
	if (ast->head->pipe_exists)
		dup2(ast->head->pipe[WRITE_END], STDOUT_FILENO);
	if (out_exists(ast))
		dup2(*(ast->head->out_fd), STDOUT_FILENO);
	close_pipes(data);
	execute_command(cmd, ast, data);
}

void	call_parent(pid_t pid, t_ast *ast, t_data *data)
{
	data->pids[data->curr_pid].ast = ast;
	data->pids[data->curr_pid].pid = pid;
	data->curr_pid++;
	if (ast->prev_exists && !in_exists(ast))
		close(ast->prev_pipe[READ_END]);
	else if (in_exists(ast))
		close(*(ast->in_fd));
	if (ast->pipe_exists)
		close(ast->pipe[WRITE_END]);
	if (out_exists(ast))
		close(*(ast->out_fd));
}

int	simple_cmd(t_data *data)
{
	t_ast	*ast;
	char	*path;
	pid_t	pid;

	ast = data->ast;
	pid = 1;
	path = NULL;
	if (!command_redirs(data, ast))
		return (data->exit_status);
	if (ast->right->cmd && ast->right->cmd[0])
		path = get_cmd_path(ast->right->cmd[0], data);
	if (is_builtin(data))
		builtins(data);
	else if (ast->token->value && ast->token->value[0])
		prep_command_execution(pid, data, ast, path);
	if (path)
		free(path);
	return (data->exit_status);
}
