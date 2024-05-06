/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:40:20 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/06 16:17:18 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_ast	*new_ast(t_token *token)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit(1);
	printf("New node of type (%d) from token index (%d)\n", token->type, token->index);
	new_node->end_flag = 0;
	new_node->type = token->type - 1;
	new_node->left = NULL;
	new_node->right = NULL;
	if (new_node->type == NODE_CMD)
		new_node = parse_cmd(token, new_node);
	return (new_node);
}

void	add_left_ast(t_ast *ast, t_ast *new_node)
{
	t_ast	*tmp;

	if (!ast)
		ast = new_node;
	else
	{
		tmp = ast;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = new_node;
	}
}

void	add_right_ast(t_ast *ast, t_ast *new_node)
{
	t_ast	*tmp;

	if (!ast)
		ast = new_node;
	else
	{
		tmp = ast;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
	}
}
