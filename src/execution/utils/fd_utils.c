/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:07:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 15:09:08 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_ast *ast)
{
	if (ast->in_fd)
		close(*(ast->in_fd));
	if (ast->out_fd)
		close(*(ast->out_fd));
}

static void	recursive_closing_fd(t_ast	*ast)
{
	if (!ast)
		return ;
	recursive_closing_fd(ast->left);
	recursive_closing_fd(ast->right);
	if (ast->type == NODE_CMD)
		close_fd(ast);
}

void	close_files(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	while (ast->head)
		ast = ast->head;
	recursive_closing_fd(ast);
}
