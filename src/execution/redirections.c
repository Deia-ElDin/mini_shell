/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:55 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/05 11:19:27 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_redirs(t_ast *ast)
{
	if (!ast || ast->type > NODE_WORD)
		return (0);
	if (ast->redir_out && ast->redir_out->exists)
	{
		if (!redirect_out(ast))
			return (0);
	}
	else if (ast->redir_in && ast->redir_in->exists)
	{
		if (!redirect_in(ast))
			return (0);
	}
	else if (ast->redir_append && ast->redir_append->exists && !append(ast))
		return (0);
	else if (ast->type == NODE_WORD)
		return (1);
	return (1);
}

int	redirect_in(t_ast *ast)
{
	ast->redir_in->fd = open(ast->redir_in->file, O_RDONLY, 0755);
	if (ast->redir_in->fd == -1)
		return (0);
	return (1);
}

int	redirect_out(t_ast *ast)
{
	ast->redir_out->fd = open(ast->redir_out->file, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (ast->redir_out->fd == -1)
		return (0);
	return (1);
}

int	append(t_ast *ast)
{
	ast->redir_append->fd = open(ast->redir_append->file, O_CREAT | O_WRONLY | O_APPEND, 0755);
	if (ast->redir_append->fd == -1)
		return (0);
	return (1);
}
