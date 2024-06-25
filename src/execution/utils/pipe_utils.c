/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 16:30:54 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_first_pipe(t_ast *ast)
{
	if (ast->left && ast->left->type == NODE_PIPE)
		return (0);
	else
		return (1);
}

int	is_last_pipe(t_ast *ast)
{
	if (ast->head && ast->head->type == NODE_PIPE)
		return (0);
	else
		return (1);
}

static void	close_pipe(t_ast *ast)
{
	if (ast->pipe_exists)
	{
		close(ast->pipe[WRITE_END]);
		close(ast->pipe[READ_END]);
	}
	if (ast->in_fd)
		close(*(ast->in_fd));
	if (ast->out_fd)
		close(*(ast->out_fd));
}

static void	recursive_closing(t_ast	*ast)
{
	if (!ast)
		return ;
	recursive_closing(ast->left);
	recursive_closing(ast->right);
	if (ast->type == NODE_CMD)
		close_pipe(ast);
}

void	close_pipes(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	while (ast->head)
		ast = ast->head;
	recursive_closing(ast);
}
