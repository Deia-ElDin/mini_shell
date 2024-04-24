/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:02:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/22 18:08:58 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast	*new_ast(int type)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit(1);
	new_node->type = type - 2;
	new_node->left = NULL;
	new_node->right = NULL;
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
