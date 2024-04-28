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

void	execution(t_data *data)
{
	builtins(data);
}

int	exec_ast(t_ast *ast, t_data *data)
{
	if (!data)
		return (1);
	if (ast->type == NODE_CMD)
		simple_cmd(ast->left, ast->right, data);
	else if (ast->type == NODE_PIPE)
		pipe_cmd(ast, data);
	else if (ast->type == NODE_OR)
		or_operator(ast, data);
	else if (ast->type == NODE_AND)
		and_operator(ast, data);
	else
	{
		if (ast->left->left || ast->left->right)
			exec_ast(ast->left, data);
		if (ast->right->left || ast->right->right)
			exec_ast(ast->right, data);
	}
	return (0);
}
