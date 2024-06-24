/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:55 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/20 18:35:50 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_heredoc(t_ast *ast, t_ast *head)
{
	ast->heredoc->fd = open(ast->heredoc->file, O_RDONLY, 0755);
	if (ast->heredoc->fd == -1)
		return (0);
	head->in_fd = &(ast->heredoc->fd);
	return (1);
}

static int	redirect_in(t_ast *ast, t_ast *head)
{
	struct stat	path_stat;

	if (access(ast->redir_in->file, F_OK))
		return (print_error(ast->redir_in->file,
				"No such file or directory"), 0);
	stat(ast->redir_in->file, &path_stat);
	if (!(path_stat.st_mode & S_IRUSR))
		return (print_error(ast->redir_in->file,
				"Permission denied"), 0);
	ast->redir_in->fd = open(ast->redir_in->file, O_RDONLY, 0755);
	if (ast->redir_in->fd == -1)
		return (0);
	head->in_fd = &(ast->redir_in->fd);
	return (1);
}

static int	redirect_out(t_ast *ast, t_ast *head)
{
	struct stat	path_stat;

	stat(ast->redir_out->file, &path_stat);
	if (!access(ast->redir_out->file, F_OK)
		&& !(path_stat.st_mode & S_IWUSR))
		return (print_error(ast->redir_out->file,
				"Permission denied"), 0);
	ast->redir_out->fd = open(ast->redir_out->file,
			O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (ast->redir_out->fd == -1)
		return (0);
	head->out_fd = &(ast->redir_out->fd);
	return (1);
}

static int	append(t_ast *ast, t_ast *head)
{
	struct stat	path_stat;

	stat(ast->redir_append->file, &path_stat);
	if (!access(ast->redir_append->file, F_OK)
		&& !(path_stat.st_mode & S_IWUSR))
		return (print_error(ast->redir_append->file,
				"Permission denied"), 0);
	ast->redir_append->fd = open(ast->redir_append->file,
			O_CREAT | O_WRONLY | O_APPEND, 0755);
	if (ast->redir_append->fd == -1)
		return (0);
	head->out_fd = &(ast->redir_append->fd);
	return (1);
}

int	check_for_redirs(t_ast *ast)
{
	t_ast	*head;

	head = ast;
	while (head && head->head && head->type != NODE_CMD)
		head = head->head;
	while (ast && ast->type == NODE_REDIR)
	{
		if (ast->redir_out->exists && !redirect_out(ast, head))
			return (0);
		else if (ast->redir_in->exists && !redirect_in(ast, head))
			return (0);
		else if (ast->redir_append->exists && !append(ast, head))
			return (0);
		else if (ast->heredoc->exists && !redirect_heredoc(ast, head))
			return (0);
		ast = ast->right;
	}
	return (1);
}
