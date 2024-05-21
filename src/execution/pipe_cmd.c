/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 15:04:55 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_prev_pipe(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	data->now_pipe[0] = ast->pipe[0];
	data->now_pipe[1] = ast->pipe[1];
	while (ast)
	{
		ast = ast->left;
		if (ast && ast->type == NODE_PIPE)
		{
			data->prev_pipe[0] = ast->pipe[0];
			data->prev_pipe[1] = ast->pipe[1];
			return (1);
		}
		else
		{
			data->prev_pipe[0] = -1;
			data->prev_pipe[1] = -1;
		}
	}
	return (0);
}

static void	execute(char *path, t_data *data)
{
	if (path)
		execve(path, data->ast->right->cmd, data->env);
	ft_putstr_fd("child execution FAILED\n", 2);
	exit(1);

}

static int	exec_pipe_cmd(pid_t *pid, t_ast *ast, t_data *data)
{
	char	*path;

	path = get_cmd_path(ast->left->cmd[0], data);
	if (!check_for_redirs(ast->right, data))
		return (data->file_fd);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("REDIRECTION ERROR\n", 2), 1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (ft_putstr_fd("FORK ERROR\n", 2), 1);
	else if (pid[0] == 0)
	{
		if (!is_first_pipe(ast))
			dup2(data->prev_pipe[0], STDIN_FILENO);
		if (!is_last_pipe(ast))
			dup2(data->now_pipe[1], STDOUT_FILENO);
		close(data->prev_pipe[0]);
		close(data->prev_pipe[1]);
		close(data->now_pipe[0]);
		close(data->now_pipe[1]);
		if (ast->left && ast->right)
		{
			data->ast = ast;
			if (ast->type == NODE_CMD && !is_builtin(data))
				execute(path, data);
			else
			{
				execution(data);
				exit(0);
			}
		}
	}
	return (pid[0]);
}

int	pipe_cmd(t_data *data)
{
	int		prev;
	t_ast	*ast;
	pid_t	pid[2];

	ast = data->ast;
	prev = get_prev_pipe(data);
	if (prev)
		dup2(data->prev_pipe[0], 1);
	data->ast = ast->left;
	pid[0] = exec_pipe_cmd(pid, ast->left, data);
	data->ast = ast->right;
	pid[1] = exec_pipe_cmd(pid, ast->right, data);
	close(data->now_pipe[0]);
	close(data->now_pipe[1]);
	waitpid(pid[0], &data->exit_status, WNOHANG);
	if (prev)
		waitpid(pid[1], &data->exit_status, WNOHANG);
	else
		waitpid(pid[1], &data->exit_status, 0);
	return (0);
}
