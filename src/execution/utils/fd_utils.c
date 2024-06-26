/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:07:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/26 14:34:15 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_ast *ast)
{
	if (!ast)
		return ;
	while (ast && ast->type == NODE_REDIR)
	{
		if (ast->redir_out->exists && ast->redir_out->fd >= 3
			&& close(ast->redir_out->fd))
			return ;
		else if (ast->redir_in->exists && ast->redir_in->fd >= 3
			&& close(ast->redir_in->fd))
			return ;
		else if (ast->redir_append->exists && ast->redir_append->fd >= 3
			&& close(ast->redir_append->fd))
			return ;
		else if (ast->heredoc->exists && ast->heredoc->fd >= 3
			&& close(ast->heredoc->fd))
			return ;
		ast = ast->right;
	}
	return ;
}

static void	recursive_closing_fd(t_ast	*ast)
{
	if (!ast)
		return ;
	recursive_closing_fd(ast->left);
	recursive_closing_fd(ast->right);
	if (ast->type == NODE_CMD)
		close_fd(ast->right->right);
}

void	close_files(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	while (ast && ast->head)
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
	if ((ast->in_fd && *(ast->in_fd) == -1)
		|| (ast->out_fd && *(ast->out_fd) == -1))
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
