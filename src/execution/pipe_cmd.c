/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 18:08:03 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_prev_pipe(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	data->now_pipe = ast->pipe;
	if (ast->left && ast->left->type == NODE_PIPE)
	{
		ast->thereisprev = true;
		ast->prev_pipe = ast->left->pipe;
		return (1);
	}
	return (0);
}

static void	execute(char *path, t_data *data)
{
	// ft_putstr_fd("INSIDE EXECUTE FUNCTION\n", 2);
	// if (data->ast->left && data->ast->left->cmd)
	// {
	// 	ft_putstr_fd("	IN EXEC: CURRENT CMD: ", 2);
	// 	ft_putstr_fd(data->ast->left->cmd[0], 2);
	// 	ft_putstr_fd("\n", 2);
	// }
	// else
	// 	ft_putstr_fd("	IN EXEC WITHOUT CMD\n", 2);
	if (data->ast->left && data->ast->right)
	{
		if (data->ast->type == NODE_CMD && !is_builtin(data))
		{
			// ft_putstr_fd("GOING TO EXECVE\n", 2);
			if (path)
				execve(path, data->ast->right->cmd, data->env);
			// ft_putstr_fd("child execution FAILED\n", 2);
			exit(1);
		}
		else
		{
			// ft_putstr_fd("GOING TO EXECUTION FROM PIPE\n", 2);
			execution(data);
			exit(0);
		}
	}
}

static void child(t_ast *ast, t_data *data)
{
	ft_putstr_fd("INSIDE CHILD PROCESS\n", 2);
	if (ast->left && ast->left->cmd)
	{
		ft_putstr_fd("	CURRENT CMD: ", 2);
		ft_putstr_fd(ast->left->cmd[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd("	IN CHILD WITHOUT CMD\n", 2);
	if (ast == ast->head->left)
	{
		dup2(data->now_pipe[1], STDOUT_FILENO);
		close (data->now_pipe[0]);
		close (data->now_pipe[1]);
	}
	else if (ast == ast->head->right && is_last_pipe(ast->head))
	{
		dup2(data->now_pipe[0], STDIN_FILENO);
		close (data->now_pipe[0]);
		close (data->now_pipe[1]);
	}
	if (ast->type != NODE_CMD)
		execute(NULL, data);
	if (ast->head->thereisprev)
	{
		ft_putstr_fd("	There is prev pipe\n", 2);
		dup2(ast->head->prev_pipe[READ_END], data->now_pipe[READ_END]);
		close(ast->head->prev_pipe[READ_END]);
	}
	close(data->now_pipe[READ_END]);
	dup2(data->now_pipe[WRITE_END], STDOUT_FILENO);
	close(data->now_pipe[WRITE_END]);
	if (ast->right->type < NODE_WORD)
		dup2(ast->right->file_fd, STDOUT_FILENO);
	execute(get_cmd_path(ast->left->cmd[0], data), data);
}

static int	exec_pipe_cmd(t_ast *ast, t_data *data, int *is_sleep)
{
	pid_t	pid;

	if (!check_for_redirs(ast->right))
		return (ast->right->file_fd);
	if (ast->right->type < NODE_WORD && ast->right->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	if (ast->left->type == NODE_WORD && ft_strnstr(ast->left->cmd[0], "sleep", ft_strlen(ast->left->cmd[0])))
		*is_sleep = 1;
	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("FORK ERROR\n", 2), 1);
	else if (pid == 0)
		child(ast, data);
	else
	{
		close(data->now_pipe[WRITE_END]);
		if (ast->thereisprev)
			close(ast->prev_pipe[READ_END]);
		if (is_sleep)
			data->exit_status = check_for_sleep(pid, "sleep", ast->right->end_flag);
		else
			data->exit_status = check_for_sleep(pid, NULL, ast->right->end_flag);
	}
	return (pid);
}

int	pipe_cmd(t_data *data)
{
	int		is_sleep;
	t_ast	*ast;

	is_sleep = 0;
	ast = data->ast;
	get_prev_pipe(data);
	// ft_putstr_fd("GOING LEFT\n", 2);
	data->ast = ast->left;
	exec_pipe_cmd(ast->left, data, &is_sleep);
	// ft_putstr_fd("GOING RIGHT\n", 2);
	data->ast = ast->right;
	exec_pipe_cmd(ast->right, data, &is_sleep);
	return (0);
}
