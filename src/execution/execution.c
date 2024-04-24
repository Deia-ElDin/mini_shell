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

void	exec_ast(t_ast *ast, t_data *data)
{
	if (!data)
		return ;
	if (ast->type == NODE_CMD && ast->left->type == NODE_WORD
		&& ast->right->type == NODE_WORD)
		simple_cmd(ast->left, ast->right, data);
	if (ast->type == NODE_PIPE)
		pipe_cmd(data);
	if (ast->left->left || ast->left->right)
		exec_ast(ast->left, data);
	if (ast->right->left || ast->right->right)
		exec_ast(ast->right, data);
	// if (ast->type == NODE_REDIR_IN)

	// if (ast->type == NODE_REDIR_OUT)

	// if (ast->type == NODE_HEREDOC)

	// if (ast->type == NODE_APPEND)

	// if (ast->type == NODE_PIPE)

	// if (ast->type == NODE_OR)

	// if (ast->type == NODE_AND)
}
