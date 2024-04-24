/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:26:03 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/12 12:26:04 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_pipe(int pid, char *cmd)
{
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd)))
		waitpid(pid, NULL, 0);
}

static int reset_fds(t_data *data)
{
    if (close (data->pipe[0]) || close (data->pipe[1])
        || dup2(data->saved_stdfds[0], 0)
        || dup2(data->saved_stdfds[1], 1))
        return (1);
    return (0);
}

static int	simple_cmd(t_ast *ast_left, t_ast *ast_right, t_data *data)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid < 0)
        exit(1);
	if (pid == 0)
	{
        if ((!ast_left->end_flag || !ast_right->end_flag)
            && (data->pipe[0] >= 0 || data->pipe[1] >= 0)
            && reset_fds(data))
            exit(1);
        execve(ast_left->cmd, ast_right->args, data->env);
	    exit(1);
    }
	if ((!ast_left->end_flag || !ast_right->end_flag)
            && (data->pipe[0] >= 0 || data->pipe[1] >= 0)
            && reset_fds(data))
            waitpid(pid, &status, 0);
    check_pipe(pid, ast_left->cmd);
    if (data->pipe[0] >= 0 || data->pipe[1] >= 0)
	    return (close(data->pipe[1]), dup2(data->pipe[0], 0), status);
    else
        return (status);
}

static int	pipe_cmd(t_data *data)
{
	if (pipe(data->pipe) == -1)
        return (-1);
	close(data->pipe[0]);
	dup2(data->pipe[1], 1);
    return (0);
}

void	execution(t_data *data)
{
	builtins(data);
}

void	exec_ast(t_ast *ast, t_data *data)
{
    if ((!ast->left || !ast->right) || !data)
        return ;
    if (ast->type == NODE_CMD)
        simple_cmd(ast->left, ast->right, data);
    if (ast->type == NODE_PIPE)
        pipe_cmd(data);
    exec_ast(ast->left, data);
    exec_ast(ast->right, data);
    // if (ast->type == NODE_REDIR_IN)

    // if (ast->type == NODE_REDIR_OUT)

    // if (ast->type == NODE_HEREDOC)

    // if (ast->type == NODE_APPEND)

    // if (ast->type == NODE_PIPE)

    // if (ast->type == NODE_OR)

    // if (ast->type == NODE_AND)

    // printf("executing ast\n");
    // if (ast->type == TOKEN_WORD)
    // {
    // }
    // else if (ast->type == NODE_LOGIC)
    //     exec_logic_cmd(ast->logic_cmd, data);
    // else if (ast->type == NODE_LIST)
    //     exec_list_cmd(ast->list_cmd, data);
    // else if (ast->type == NODE_SEPARATOR)
    //     exec_separator_cmd(ast->separator_cmd, data);
    // else if (ast->type == NODE_LOOP)
    //     exec_loop_cmd(ast->loop_cmd, data);
    // else if (ast->type == NODE_FUNCTION)
    //     exec_function_cmd(ast->function_cmd, data);
    // else if (ast->type == NODE_FOR)
    //     exec_for_cmd(ast->for_cmd, data);
    // else if (ast->type == NODE_WHILE)
    //     exec_while_cmd(ast->while_cmd, data);
    // else if (ast->type == NODE_UNTIL)
    //     exec_until_cmd(ast->until_cmd, data);
    // else if (ast->type == NODE_IF)
    //     exec_if_cmd(ast->if_cmd, data);
    // else if (ast->type == NODE_CASE)
    //     exec_case_cmd(ast->case_cmd, data);
    // else if (ast->type == NODE_BRACE)
    //     exec_brace_cmd(ast->brace_cmd, data);
    // else if (ast->type == NODE_SUBSHELL)
    //     exec_subshell_cmd(ast->subshell_cmd, data);
    // else if (ast->type == NODE_ARITHMETIC)
    //     exec_arithmetic_cmd(ast->arithmetic_cmd, data);
    // else if (ast->type == NODE_ASSIGNMENT)
    //     exec_assignment_cmd(ast
}
