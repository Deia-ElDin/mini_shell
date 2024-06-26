/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:57:46 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/26 11:32:19 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_exists(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == NODE_REDIR
			&& (ast->redir_in->exists || ast->heredoc->exists))
			return (1);
		ast = ast->right;
	}
	return (0);
}

int	out_exists(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == NODE_REDIR
			&& (ast->redir_out->exists || ast->redir_append->exists))
			return (1);
		ast = ast->right;
	}
	return (0);
}

static void	recursive_opening_fd(t_ast	*ast)
{
	if (!ast)
		return ;
	recursive_opening_fd(ast->left);
	recursive_opening_fd(ast->right);
	if (ast->type == NODE_CMD)
		check_for_redirs(ast->right->right);
}

void	open_all_redirs(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	while (ast->head)
		ast = ast->head;
	recursive_opening_fd(ast);
}

