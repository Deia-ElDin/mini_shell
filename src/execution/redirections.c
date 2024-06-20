/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:55 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/20 10:46:15 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_redirs(t_ast *ast)
{
	if (!ast || ast->type > NODE_WORD)
		return (0);
	if (ast->type == NODE_REDIR_OUT)
	{
		if (!redirect_out(ast))
			return (1);
	}
	else if (ast->type == NODE_REDIR_IN)
	{
		if (!redirect_in(ast))
			return (1);
	}
	else if (ast->type == NODE_APPEND && !append(ast))
		return (1);
	else if (ast->type == NODE_WORD)
		return (1);
	if (ast->type < NODE_WORD && ast->head->file_fd == -1)
		return (print_error(ast->file, "No such file or directory"), 0);
	return (0);
}

int	redirect_in(t_ast *ast)
{
	ast->head->in_exists = true;
	ast->head->file_fd = open(ast->file, O_RDONLY, 0755);
	if (ast->head->file_fd == -1)
		return (1);
	return (0);
}

int	redirect_out(t_ast *ast)
{
	ast->head->out_exists = true;
	unlink(ast->file);
	ast->head->file_fd = open(ast->file, O_CREAT | O_WRONLY, 0755);
	if (ast->head->file_fd == -1)
		return (1);
	return (0);
}

int	append(t_ast *ast)
{
	ast->head->out_exists = true;
	ast->head->file_fd = open(ast->file, O_CREAT | O_WRONLY | O_APPEND, 0755);
	if (ast->head->file_fd == -1)
		return (1);
	return (0);
}
