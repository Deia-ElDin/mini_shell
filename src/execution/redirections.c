/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:55 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 16:52:37 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_redirs(t_ast *ast)
{
	if (!ast)
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
	else if (ast->type == NODE_HEREDOC && !here_doc(ast))
		return (1);
	else if (ast->type == NODE_APPEND && !append(ast))
		return (1);
	else if (ast->type == NODE_WORD || ast->type == NODE_CMD)
		return (1);
	return (0);
}

int	redirect_in(t_ast *ast)
{
	ast->file_fd = open(ast->file, O_RDONLY, 0755);
	if (ast->file_fd == -1)
		return (1);
	dup2(ast->file_fd, 0);
	return (0);
}

int	redirect_out(t_ast *ast)
{
	unlink(ast->file);
	ast->file_fd = open(ast->file, O_CREAT | O_WRONLY, 0755);
	if (ast->file_fd == -1)
		return (1);
	dup2(ast->file_fd, 1);
	return (0);
}

int	here_doc(t_ast *ast)
{
	int	status;

	(void)ast;
	status = 0;
	return (status);
}

int	append(t_ast *ast)
{
	ast->file_fd = open(ast->file, O_CREAT | O_WRONLY | O_APPEND, 0755);
	if (ast->file_fd == -1)
		return (1);
	dup2(ast->file_fd, 1);
	return (0);
}
