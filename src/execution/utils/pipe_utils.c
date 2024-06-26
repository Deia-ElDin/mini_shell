/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/26 14:24:53 by melshafi         ###   ########.fr       */
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
		if (ast->pipe[WRITE_END] >= 0)
			close(ast->pipe[WRITE_END]);
		if (ast->pipe[READ_END] >= 0)
			close(ast->pipe[READ_END]);
	}
	if (ast->in_fd && *(ast->in_fd) >= 0)
		close(*(ast->in_fd));
	if (ast->out_fd && *(ast->out_fd) >= 0)
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
	while (ast && ast->head)
		ast = ast->head;
	recursive_closing(ast);
}
