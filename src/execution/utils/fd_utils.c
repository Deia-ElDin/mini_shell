/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:07:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 16:52:54 by melshafi         ###   ########.fr       */
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

int	is_file(t_token *token)
{
	if (token->type != TOKEN_WORD)
		return (0);
	else if (token->prev && token->prev->type < TOKEN_WORD)
		return (1);
	else
		return (0);
}

int	command_redirs(t_data *data, t_ast *ast)
{
	if (!check_for_redirs(ast->right->right))
	{
		if (ast->pipe_exists)
			close(ast->pipe[WRITE_END]);
		data->pids[data->curr_pid].ast = NULL;
		data->pids[data->curr_pid].pid = -1;
		data->curr_pid++;
		return ((data->exit_status = 1, 0));
	}
	return (1);
}
