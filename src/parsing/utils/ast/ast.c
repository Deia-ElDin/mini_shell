/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:40:20 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/29 11:09:52 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_ast	*new_ast(t_token *token)
{
	t_ast	*new_node;
	t_heredoc *heredoc;

	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->end_flag = 0;
	new_node->type = token->type - 1;
	new_node->head = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->pipe_exists = false;
	new_node->prev_exists = false;
	new_node->in_exists = false;
	new_node->out_exists = false;
	new_node->heredoc = heredoc;
	new_node->prev_pipe = NULL;
	new_node->pipe[0] = -1;
	new_node->pipe[1] = -1;
	if (new_node->type == NODE_CMD)
		new_node = parse_cmd(token, new_node);
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	add_left_ast(t_ast *ast, t_ast *new_node)
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

void	add_right_ast(t_ast *ast, t_ast *new_node)
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
