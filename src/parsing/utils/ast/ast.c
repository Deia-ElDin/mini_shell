/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:40:20 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/10 16:37:10 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*set_ast_defaults(t_ast *ast)
{
	ast->head = NULL;
	ast->left = NULL;
	ast->right = NULL;
	ast->end_flag = 0;
	ast->pipe_exists = false;
	ast->prev_exists = false;
	ast->prev_pipe = NULL;
	ast->pipe[0] = -1;
	ast->pipe[1] = -1;
	return (ast);
}

t_ast	*ast_mem_allocate(t_ast **new_node)
{
	t_heredoc		*heredoc;
	t_redir_append	*append;
	t_redir_in		*redir_in;
	t_redir_out		*redir_out;

	append = (t_redir_append *)ft_calloc(1, sizeof(t_redir_append));
	redir_in = (t_redir_in *)ft_calloc(1, sizeof(t_redir_in));
	redir_out = (t_redir_out *)ft_calloc(1, sizeof(t_redir_out));
	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!new_node || !heredoc || !redir_in || !redir_out || !append)
		return (NULL);
	(*new_node)->heredoc = heredoc;
	(*new_node)->heredoc->exists = false;
	(*new_node)->redir_append = append;
	(*new_node)->redir_append->exists = false;
	(*new_node)->redir_in = redir_in;
	(*new_node)->redir_in->exists = false;
	(*new_node)->redir_out = redir_out;
	(*new_node)->redir_out->exists = false;
	return (*new_node);
}

t_ast	*new_ast(t_token *token)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node || !ast_mem_allocate(&new_node))
		return (NULL);
	new_node->end_flag = 0;
	if (token->type == TOKEN_PIPE)
		new_node->type = NODE_PIPE;
	else if (token->type == TOKEN_WORD)
		new_node->type = NODE_CMD;
	new_node->head = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->in_fd = NULL;
	new_node->out_fd = NULL;
	new_node->pipe_exists = false;
	new_node->prev_exists = false;
	new_node->prev_pipe = NULL;
	new_node->pipe[0] = -1;
	new_node->pipe[1] = -1;
	if (new_node->type == NODE_CMD)
		new_node = parse_cmd(token, new_node);
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	add_left_ast(t_ast *ast, t_ast (*new_node))
{
	t_ast	*tmp;

	if (!ast)
	{
		ast = new_node;
		ast->head = NULL;
	}
	else
	{
		tmp = ast;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new_node;
		new_node->head = tmp;
	}
}

void	add_right_ast(t_ast *ast, t_ast (*new_node))
{
	t_ast	*tmp;

	if (!ast)
	{
		ast = new_node;
		ast->head = NULL;
	}
	else
	{
		tmp = ast;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
		new_node->head = tmp;
	}
}
