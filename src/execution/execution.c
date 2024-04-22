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

// static void	simple_cmd(t_ast *ast_left, t_ast *ast_right, t_data *data)
// {
// 	execve(ast_left->value, &ast_right->value, data->env);
// }

void	execution(t_data *data)
{
	builtins(data);
}

void	exec_ast(t_ast *ast, t_data *data)
{
	(void) ast;
	(void) data;
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
