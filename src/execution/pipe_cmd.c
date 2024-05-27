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

static void	execute(char *path, t_data *data)
{
	if (data->ast->left && data->ast->right)
	{
		if (data->ast->type == NODE_CMD && !is_builtin(data))
		{
			if (path)
				execve(path, data->ast->right->cmd, data->env);
			ft_putstr_fd("child execution FAILED\n", 2);
			exit(1);
		}
		else if (data->ast->type == NODE_CMD && is_builtin(data))
		{
			builtins(data);
			exit(0);
		}
	}
}

static void child(t_ast *ast, t_data *data)
{
	if (ast == ast->head->left)
	{
		dup2(ast->head->pipe[1], STDOUT_FILENO);
		close (ast->head->pipe[0]);
		close (ast->head->pipe[1]);
	}
	else if (ast == ast->head->right)
	{
		dup2(ast->head->pipe[0], STDIN_FILENO);
		close (ast->head->pipe[0]);
		close (ast->head->pipe[1]);
	}
	execute(get_cmd_path(ast->left->cmd[0], data), data);
}

static int	exec_pipe_cmd(t_ast *ast, t_data *data)
{
	pid_t	pid;

	if (!check_for_redirs(ast->right))
		return (ast->right->file_fd);
	if (ast->right->type < NODE_WORD && ast->right->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("FORK ERROR\n", 2), 1);
	else if (pid == 0)
		child(ast, data);
	else
	{
		if (ast->thereisnext)
			close(ast->next_pipe[READ_END]);
		close(ast->head->pipe[WRITE_END]);
		if (ast->left->type == NODE_WORD && ft_strnstr(ast->left->cmd[0], "sleep", ft_strlen(ast->left->cmd[0])))
			data->exit_status = check_for_sleep(pid, "sleep", ast->right->end_flag);
		else
			data->exit_status = check_for_sleep(pid, NULL, ast->right->end_flag);
	}
	return (pid);
}

int	pipe_cmd(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	if (ast->left->type <= NODE_CMD)
	{
		data->ast = ast->left;
		exec_pipe_cmd(ast->left, data);
	}
	if (ast->right->type <= NODE_CMD)
	{
		data->ast = ast->right;
		exec_pipe_cmd(ast->right, data);
	}
	return (0);
}
