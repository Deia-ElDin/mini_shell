/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:57:46 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/20 18:15:44 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_temp(t_ast *ast)
{
	if (!ast)
		return (1);
	if (ast->type == NODE_REDIR && ast->heredoc->exists)
		unlink(ast->heredoc->file);
	clear_temp(ast->left);
	clear_temp(ast->right);
	return (0);
}

int	in_exists(t_ast *ast)
{
	t_ast	*head;

	head = ast;
	while (ast)
	{
		if (ast->type == NODE_REDIR && head->in_fd
			&& (ast->redir_in->exists || ast->heredoc->exists))
			return (1);
		ast = ast->right;
	}
	return (0);
}

int	out_exists(t_ast *ast)
{
	t_ast	*head;

	head = ast;
	while (ast)
	{
		if (ast->type == NODE_REDIR && head->out_fd
			&& (ast->redir_out->exists || ast->redir_append->exists))
			return (1);
		ast = ast->right;
	}
	return (0);
}
