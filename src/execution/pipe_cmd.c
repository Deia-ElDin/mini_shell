/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 13:09:49 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_next_pipe(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	data->now_pipe[0] = ast->pipe[0];
	data->now_pipe[1] = ast->pipe[1];
	while (ast)
	{
		ast = ast->head;
		if (ast && ast->type == NODE_PIPE)
		{
			data->next_pipe[0] = ast->pipe[0];
			data->next_pipe[1] = ast->pipe[1];
			return (1);
		}
		else
		{
			data->next_pipe[0] = -1;
			data->next_pipe[1] = -1;
		}
	}
	return (0);
}

static void	execute_cmd(char *path, t_data *data)
{
	if (path)
		execve(path, data->ast->right->cmd, data->env);
	ft_putstr_fd("child execution FAILED\n", 2);
	exit(1);

}

static int	exec_first_cmd(pid_t pid, t_ast *ast, t_data *data)
{
	char	*path;

	path = NULL;
	if (!check_for_redirs(ast->right, data))
		return (data->file_fd);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	pid = fork();
	if (pid == 0)
	{
		close (1);
		dup2(data->now_pipe[1], 1);
		close(data->now_pipe[0]);
		close(data->now_pipe[1]);
		data->ast = ast;
		if (data->ast->left && data->ast->right)
		{
			if (data->ast->type == NODE_CMD && !is_builtin(data))
			{
				path = get_cmd_path(data->ast->left->cmd[0], data);
				execute_cmd(path, data);
			}
			else
			{
				execution(data);
				exit(0);
			}
		}
	}
	else
		data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	return (0);
}

static int	exec_second_cmd(pid_t pid, t_ast *ast, t_data *data)
{
	char	*path;

	path = NULL;
	if (!check_for_redirs(ast->right, data))
		return (data->file_fd);
	if (data->redirect_flag != 0 && data->file_fd == -1)
		return (ft_putstr_fd("ERR\n", 2), 1);
	pid = fork();
	if (pid == 0)
	{
		close (0);
		dup2(data->now_pipe[0], 0);
		close(data->now_pipe[0]);
		close(data->now_pipe[1]);
		data->ast = ast;
		if (data->ast->left && data->ast->right)
		{
			if (data->ast->type == NODE_CMD && !is_builtin(data))
			{
				ft_putstr_fd("	Going into execute_cmd\n", 2);
				path = get_cmd_path(data->ast->left->cmd[0], data);
				execute_cmd(path, data);
			}
			else
			{
				ft_putstr_fd("	Going into execution\n", 2);
				execution(data);
				exit(0);
			}
		}
	}
	else
		data->exit_status = check_for_sleep(pid, path, ast->right->end_flag);
	return (0);
}

int	pipe_cmd(t_data *data)
{
	t_ast	*ast;
	pid_t	pid;

	pid = 0;
	ast = data->ast;
	get_next_pipe(data);
	data->ast = ast->left;
	exec_first_cmd(pid, ast->left, data);
	data->ast = ast->right;
	exec_second_cmd(pid, ast->right, data);
	close(data->now_pipe[0]);
	close(data->now_pipe[1]);
	return (0);
}

/*

Handle pipe commands manually in handle_pipe_cmd instead of simple_cmd,
Follow this heirarchy and order of pipe closures and dups:

case PIPE:
    pcmd = (struct pipecmd*)cmd;
    if(pipe(p) < 0)
      panic("pipe");
    if(fork1() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->left);
    }
    if(fork1() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait();
    wait();
    break;


SOURCE: https://github.com/mit-pdos/xv6-public/blob/master/sh.c
@line:100

*/
