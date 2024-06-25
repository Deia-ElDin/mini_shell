/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:57:46 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 14:44:17 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_exists(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == NODE_REDIR
			&& (ast->redir_in->exists || ast->heredoc->exists))
			return (1);
		ast = ast->right;
	}
	return (0);
}

int	out_exists(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == NODE_REDIR
			&& (ast->redir_out->exists || ast->redir_append->exists))
			return (1);
		ast = ast->right;
	}
	return (0);
}
