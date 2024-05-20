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

#include "minishell.h"
#include "minishell.h"

void	execution(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	if (!data || !ast)
		return ;
	if (is_builtin(data))
		builtins(data);
	else
	{
		if (ast->type == NODE_CMD)
			simple_cmd(ast->left, ast->right, data);
		else if (ast->type == NODE_PIPE)
			pipe_cmd(ast, data);
	}
}

// int	exec_ast(t_ast *ast, t_data *data)
// {
// 	if (!data || !ast)
// 		return (1);
// 	if (ast->type == NODE_CMD)
// 		simple_cmd(ast->left, ast->right, data);
// 	else if (ast->type == NODE_PIPE)
// 		pipe_cmd(ast, data);
// 	return (0);
// }
