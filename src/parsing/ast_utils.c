/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:02:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 14:30:22 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*new_ast(int token)
{
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit(1);
	new_node->token = token;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	add_ast(t_ast **ast, t_ast *new_node)
{
	t_ast	*tmp;

	if (!*ast)
		*ast = new_node;
	else
	{
		tmp = *ast;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_node;
	}
}
